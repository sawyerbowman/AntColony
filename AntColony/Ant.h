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
#include "City.h"
<<<<<<< Updated upstream
#include "AntAlgorithm.h"
=======
#include "PheromoneMap.h"
>>>>>>> Stashed changes

class Ant {
public:
    //Constructor
    Ant();
    
    void addToVisitedCities(PheromoneMap pMap);
    void clearVisitedCities();
    
    //Getters and Setters
    vector<City*> getVisitedCities() { return visitedCities; }
    
    int getTourLength() { return tourLength; }
    
private:
    vector<City*> visitedCities;
    
    int tourLength;
    
};

#endif /* defined(__AntColony__Ant__) */
