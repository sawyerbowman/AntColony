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
 *This funciton will update all pheromones (i.e. all edge probabilities)
 */

void PheromoneMap::updatePheromones(vector<Ant*> ants, double evapFactor){
    
    //First update all pheromones by the (1-rho)*tau additive factor.
    
    for(int i = 0; i < pheromoneMap.size(); i++){
        
        for(int j = 0; j < pheromoneMap.size(); j++){
            
            pheromoneMap.at(i).at(j) += (1 - evapFactor)*pheromoneMap.at(i).at(j);
            
        }
        
    }
    
    //Next update the pheromones by the delta tau summation.
    
    //Loop through all of the ants in our algorithm.
    
    for(int i = 0; i < ants.size(); i++){
        
        //Loop through an individual ant's visited cities.
        
        for(int j = 0; j < ants.at(i)->getVisitedCities().size()-1; j++){
            
            //Update the appropriate edge in the Pheromone map that corresponds
            //to the edge between the jth and jth + 1 city of that ant's tour.
            //Sum it to the current value to get the delta tau summation.
            
            pheromoneMap.at(ants.at(i)->getVisitedCities().at(j)
                ->getCityNum()-1).at(ants.at(i)->getVisitedCities().at(j+1)
                ->getCityNum()-1) += ants.at(i)->getTourLength();
            
        }
        
    }
    
}




 
