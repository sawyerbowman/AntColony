//
//  Ant.h
//  AntColony
//
//  Created by Sawyer Bowman on 3/23/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#ifndef __AntColony__Ant__
#define __AntColony__Ant__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "City.h"
#include "PheromoneMap.h"


class Ant {
public:
    //Constructor
    Ant();
    
    void createTour(PheromoneMap* pMap, vector<City*> cities, double alpha,
                    double beta, vector<vector<double>> distances, string type,
                    double epsilon, double tauNaught, double q);
    void clearVisitedCitiesAndTour();

    
    //Getters and Setters
    vector<City*> getVisitedCities() { return visitedCities; }
    
    double getTourLength() { return tourLength; }
    
private:
    vector<City*> visitedCities;
    
    double tourLength;
    
    City* addCityOnMaxEdge(vector<vector<double>> pheroMap, vector<vector<double>> distances,
                          double beta, vector<City*> remainCities, int startCityNum);
    
};

#endif /* defined(__AntColony__Ant__) */
