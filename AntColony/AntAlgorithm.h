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
#include <future>
#include <chrono>
#include <ctime>
#include <time.h>
#include <sys/time.h>

#include "Problem.h"
#include "Ant.h"
#include "City.h"
#include "PheromoneMap.h"

#define NUM_THREADS 4
#define PHER_INIT   .002

const int optimals[5] = {259045, 80450, 137694, 182566, 565530};
const int maxTime = 120;

using namespace std;

class AntAlgorithm {
public:
    //Constructors for the EAS and ACS algorithms
    AntAlgorithm(string type, string fileName, int numAnts, int iterations, double alpha,
                 double beta, double evapFactor, double eliteFactor);
    
    AntAlgorithm(string type, string fileName, int numAnts, int iterations, double alpha,
                 double beta, double evapFactor, double epsilon, double q);
    
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
    double getEpsilon() { return this->epsilon; }
    double getQ() { return this->q; }
    double getTauNaught() { return this->tauNaught; }
    
    //main function of the program
    double run(int problemNum);
    
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
    double tauNaught;
    double epsilon;
    double q;
    
    //Helper functions
    void initAnts();
    vector<City*> findBestTour();
    void runThreads();
    vector<City*> getGreedyTour();
    void calcTauNaught();
    
    
    //Elitist Pheromone Update Function
    void updatePheromones(vector<City*> bestTour, string type);
    
};

#endif /* defined(__AntColony__AntAlgorithm__) */
