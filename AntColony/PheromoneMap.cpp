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
        vector<double> newCol(cities.size(),0);
        pheromoneMap.push_back(newCol);
    }
}

/**
 *This funciton will update all pheromones (i.e. all edge probabilities) for ACS
 */

void PheromoneMap::updatePheromones(vector<City*> cities, double evapFactor,
                                    double tourLength){
    
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
                    1/tourLength;
        
    }
}



