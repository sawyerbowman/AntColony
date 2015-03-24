//
//  Problem.h
//  AntColony
//
//  Created by Sawyer Bowman on 3/23/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#ifndef __AntColony__Problem__
#define __AntColony__Problem__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "City.h"

using namespace std;

class Problem{
public:
    //Constructor
    Problem(string fileName);
    
    //Getters and Setters
    vector<City*> getCities() { return cities; }
    
private:
    //Information variables
    string name;
    string comment;
    string type;
    int dimension;
    string edgeWeightType;
    
    //Vector of cities from the problem file
    vector<City*> cities;
    
    //Helper method to parse the file
    void parseHeaderLine(string line, int count);
    
    
};

#endif /* defined(__AntColony__Problem__) */
