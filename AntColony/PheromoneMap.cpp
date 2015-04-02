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