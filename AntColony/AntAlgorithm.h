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
#include <pthread.h>
#include <thread>

#include "Problem.h"
#include "Ant.h"
#include "City.h"
#include "PheromoneMap.h"

#define NUM_THREADS 20

using namespace std;

class AntAlgorithm {
public:
    //Constructors for the EAS and ACS algorithms
    AntAlgorithm(string type, string fileName, int numAnts, int iterations, double alpha,
                 double beta, double evapFactor, double eliteFactor);
    
    AntAlgorithm(string type, string fileName, int numAnts, int iterations, double alpha,
                 double beta, double evapFactor, double epsilon,
                 double tao, double probability);
    
    string getType() { return this->type; }
    string getFileName() { return this->fileName; }
    int getNumAnts() { return this->numAnts; }
    int getIterations() { return this->iterations; }
    double getAlpha() { return this->alpha; }
    double getBeta() { return this->beta; }
    Problem* getProblem() { return this->problem; }
    PheromoneMap* getMap() { return this->map; }
    double getEliteFactor() { return this->eliteFactor; }
    double getBSF() { return this->bsf; }
    
    //main function of the program
    void run();
    
private:
    //Shared Variables
    string type;
    string fileName;
    int numAnts;
    int iterations;
    double alpha;
    double beta;
    double evapFactor;
    Problem* problem;
    PheromoneMap* map;
    
    //TODO: should we use a vector or dynamic array here?
    vector<Ant*> ants;
    
    //for EAS
    double eliteFactor;
    double bsf;
    
    //For ACS
    double epsilon;
    double tao;
    double probability;
    
    //Helper functions
    void initAnts();
    vector<City*> findBestTour();
    
    //Elitist Pheromone Update Function
    void eliteUpdatePheromones(vector<City*> bestTour);
    
    
};

#endif /* defined(__AntColony__AntAlgorithm__) */
