//
//  PheromoneMap.cpp
//  AntColony
//
//  Created by Sawyer Bowman on 3/23/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include "PheromoneMap.h"

/**
 *The constructor function reads in a vector of the cities and then creates a
 *vector of pheromones of size n(n-1)/2 where n is the number of cities.  These
 *values represent the pheromone levels for each each between each city.  The
 *initial pheromone level is set to zero.
 */

PheromoneMap::PheromoneMap(vector<City*> cities){
    
    //create a vector of all edges.
    
    for(int i = 0; i < cities.size(); i++){
        
        for(int j = 0; j < cities.size(); j++){
            
            //initially set all the pheromone levels to zero.
            
            pheromoneMap.at(i).at(j) = 0;
            
        }
        
    }
    
}

/**
 *This funciton will update all pheromones (i.e. all edge probabilities) for ACS
 */

void PheromoneMap::updatePheromones(vector<City*> cities, double evapFactor){
    
    //First update all pheromones by the (1-rho)*tau additive factor.
    
    for(int i = 0; i < pheromoneMap.size(); i++){
        
        for(int j = 0; j < pheromoneMap.size(); j++){
            
            pheromoneMap.at(i).at(j) += (1 - evapFactor)*pheromoneMap.at(i).at(j);
            
        }
        
    }
    
    //Next update the pheromones by the delta tau summation.
        
    //Loop through an individual ant's visited cities.
        
    for(int j = 0; j < cities.size()-1; j++){
        
        //Update the appropriate edge in the Pheromone map that corresponds
        //to the edge between the jth and jth + 1 city of that ant's tour.
        //Sum it to the current value to get the delta tau summation.
        
        pheromoneMap[cities[j]->getCityNum()][cities[j+1]->getCityNum()] +=
                    cities[j]->calcDistance(cities[j+1]);
        
//        pheromoneMap.at(ants.at(i)->getVisitedCities().at(j)
//                        ->getCityNum()-1).at(ants.at(i)->getVisitedCities().at(j+1)
//                                             ->getCityNum()-1) += ants.at(i)->getTourLength();
        
    }
}

/**
 *This function will update all pheromones for the elitist ant colony system
 */

void PheromoneMap::eliteUpdatePheromones(vector<City*> cities, double evapFactor,
                                         double eliteFactor, double bsf){
    
    //First update all pheromones by the (1-rho)*tau additive factor.
    
    for(int i = 0; i < pheromoneMap.size(); i++){
        
        for(int j = 0; j < pheromoneMap.size(); j++){
            
            //update by the tau factor
            
            pheromoneMap.at(i).at(j) += (1 - evapFactor)*pheromoneMap.at(i).at(j);
            
        }
        
    }
    
    //Then update the pheromones by the elitist delta tau.
    
    for(int i = 0; i < cities.size()-1; i++){
        
        int index1 = cities[i]->getCityNum();
        int index2 = cities[i+1]->getCityNum();
        
        pheromoneMap[index1][index2] += 1/bsf;
        
    }
    
    //Next update the pheromones by the delta tau summation.
    
    
    //Loop through an individual ant's visited cities.
    
    for(int j = 0; j < cities.size()-1; j++){
        
        //Update the appropriate edge in the Pheromone map that corresponds
        //to the edge between the jth and jth + 1 city of that ant's tour.
        //Sum it to the current value to get the delta tau summation.
        
        pheromoneMap[cities[j]->getCityNum()-1][cities[j+1]->getCityNum()-1] +=
                    cities[j]->calcDistance(cities[j+1]);
        
        //            pheromoneMap.at(ants.at(i)->getVisitedCities().at(j)
        //                            ->getCityNum()-1).at(ants.at(i)->getVisitedCities().at(j+1)
        //                                                 ->getCityNum()-1) += ants.at(i)->getTourLength();
        
    }
    
}





