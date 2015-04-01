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
    vector<City*> getCities() { return this->cities; }
    
    vector<vector<double>> getCityDistances() { return this->cityDistances; }
    
private:
    //Information variables
    string name;
    string comment;
    string type;
    int dimension;
    string edgeWeightType;
    
    //Vector of cities from the problem file
    vector<City*> cities;
    
    //Vector of Vectors to hold city distances
    vector<vector<double>> cityDistances;
    
    //Helper method to parse the file
    void parseHeaderLine(string line, int count);
    
    //Helper method to init distances (dynamic programming)
    void initCityDistances();
    
    
};

#endif /* defined(__AntColony__Problem__) */
