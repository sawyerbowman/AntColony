//
//  City.cpp
//  AntColony
//
//  Created by Sawyer Bowman on 3/23/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include "City.h"

/**
 *A constructor for a city takes in a line containing a city number, lat, and lon.
 *It then parses the line and create an object from each word.
 */

City::City(string line){
    string word;
    stringstream lineParser (line);
    int count = 1;
    while(lineParser >> word){
        switch (count) {
            case 1:
                this->cityNum = stoi(word);
                break;
            case 2:
                this->lat = stod(word);
                break;
            case 3:
                this->lon = stod(word);
                break;
        }
        count++;
    }
}

/**
 *This method calculates the distance between any two cities using the distance
 *formula.
 */

double City::calcDistance(City* city2){
    return sqrt(pow((this->lat - city2->getLat()), 2) +  pow((this->lon -
                city2->getLon()), 2));
}
