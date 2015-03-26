//
//  PheromoneMap.h
//  AntColony
//
//  Created by Sawyer Bowman on 3/23/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#ifndef __AntColony__PheromoneMap__
#define __AntColony__PheromoneMap__

#include <stdio.h>
#include <vector>
#include "City.h"
#include "Ant.h"
#include "AntAlgorithm.h"

using namespace std;

class PheromoneMap {
public:
    
    //Constructor function
    PheromoneMap(vector<City*> cities);
    
    //Pheromone Update function
    void updatePheromones(vector<Ant*> ants, double evapFactor);
    
    
private:
    
    //2D Vector of all pheromones for all edges of the graph of cities
    vector<vector<double>> pheromoneMap;
    
    
    
};

#endif /* defined(__AntColony__PheromoneMap__) */
