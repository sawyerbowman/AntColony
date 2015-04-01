//
//  Problem.cpp
//  AntColony
//
//  Created by Sawyer Bowman on 3/23/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include "Problem.h"

/**
 *The constructor for a problem reads the filename specified in the command line
 *arguments and creates a vector of cities as well as filling in other useful
 *variables (like dimension, name, type, comment, and edgeWeightType).
 */

Problem::Problem(string fileName){
    //Try to read in the file
    ifstream problemFile(fileName);
    
    //String to hold each line
    string line;
    
    //If file is valid, continue parsing
    if (problemFile.is_open()){
        int count = 1;
        while (getline(problemFile, line)){
            //parse first five lines
            if (count < 7){
                //skip the header line for the main data
                if (count == 6){
                    count++;
                    continue;
                }
                parseHeaderLine(line, count);
                count++;
            }
            //check if end of file
            else if (line == "EOF"){
                continue;
            }
            //parse each line and put it into a vector of cities
            else {
                City* newCity = new City(line);
                this->cities.push_back(newCity);
            }
        }
        problemFile.close();
    }
    
    //If file invalid, print out error message and quit
    else {
        cout << "Please enter a valid file name. This name could not open a file." << endl;
        exit(1);
    }
    
    //Create a vector of vector of distances between each pair of cities for later use
    initCityDistances();
}

/**
 *Takes the first line and assigns the appropriate parts of the line
 *to the correct variable. (Assumes the structure in the handout)
 */

void Problem::parseHeaderLine(string line, int count){
    //find substring after : to get relevent words from file
    size_t pos = line.find(": ");
    line = line.substr(pos+2);
    switch (count){
        case 1:
            this->name = line;
            break;
        case 2:
            this->comment = line;
            break;
        case 3:
            this->type = line;
            break;
        case 4:
            this->dimension = stoi(line);
            break;
        case 5:
            this->edgeWeightType = line;
    }
}

/**
 *Initialize a vector of vectors that holds every distance between any pair
 *of cities from the problem
 */

void Problem::initCityDistances(){
    for (int i = 0; i < this->cities.size(); i++){
        vector<double> col;
        this->cityDistances.push_back(col);
        for (int j = 0; j < this->cities.size(); j++){
            this->cityDistances[i].push_back(cities[i]->calcDistance(cities[j]));
        }
    }
}


