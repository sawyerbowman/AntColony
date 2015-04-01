//
//  City.h
//  AntColony
//
//  Created by Sawyer Bowman on 3/23/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#ifndef __AntColony__City__
#define __AntColony__City__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

class City {
public:
    //Constructor
    City(string line);
    
    //Getters
    int getCityNum() { return cityNum; }
    double getLat() { return lat; }
    double getLon() { return lon; }
    
    //Find distance between this city and another city
    double calcDistance(City* city2);
    
private:
    int cityNum;
    double lat;
    double lon;
};

#endif /* defined(__AntColony__City__) */
