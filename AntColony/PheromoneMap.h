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

using namespace std;

class PheromoneMap {
public:
    
    //Constructor function
    PheromoneMap(vector<City*> cities);
    
    //Pheromone Update function
    void updatePheromones(vector<City*> ants, double evapFactor, double tourLength);
    
    //Elitist Pheromone Update Function
    void eliteUpdatePheromones(vector<City*> ants, double evapFactor, double
                               eliteFactor, double bsf, double tourLength);
    
    vector<vector<double>> getPheromoneMap(){return pheromoneMap;}
    
    
private:
    
    //2D Vector of all pheromones for all edges of the graph of cities
    vector<vector<double>> pheromoneMap;
    
    
    
};

#endif /* defined(__AntColony__PheromoneMap__) */
