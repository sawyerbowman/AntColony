//
//  AntAlgorithm.h
//  AntColony
//
//  Created by Sawyer Bowman on 3/23/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#ifndef __AntColony__AntAlgorithm__
#define __AntColony__AntAlgorithm__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Problem.h"
#include "City.h"
#include "Ant.h"

using namespace std;

class AntAlgorithm {
public:
    //Constructors for the EAS and ACS algorithms
    AntAlgorithm(string type, string fileName, int numAnts, int iterations, double pheromoneInfluence,
                 double heuristicInfluence, double evapFactor, double eliteFactor);
    
    AntAlgorithm(string type, string fileName, int numAnts, int iterations, double pheromoneInfluence,
                 double heuristicInfluence, double evapFactor, double epsilon,
                 double tao, double probability);
    
    //main function of the program
    void run();
    
private:
    //Shared Variables
    string type;
    string fileName;
    int numAnts;
    int iterations;
    double pheromoneInfluence;
    double heuristicInfluence;
    double evapFactor;
    Problem* problem;
    
    //TODO: should we use a vector or dynamic array here?
    vector<Ant*> ants;
    
    //for EAS
    double eliteFactor;
    
    //For ACS
    double epsilon;
    double tao;
    double probability;
    
    void initAnts();
    
    
};

#endif /* defined(__AntColony__AntAlgorithm__) */
