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

class Ant {
public:
    //Constructor
    Ant();
    
    void addToVisitedCities();
    void clearVisitedCities();
    
    //Getters and Setters
    vector<City*> getVisitedCities() { return visitedCities; }
    
private:
    vector<City*> visitedCities;
    
};

#endif /* defined(__AntColony__Ant__) */
