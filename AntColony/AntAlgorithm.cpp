//
//  AntAlgorithm.cpp
//  AntColony
//
//  Created by Sawyer Bowman on 3/23/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include "AntAlgorithm.h"

/**
 *The constructor for EAS
 */

AntAlgorithm::AntAlgorithm(string type, string fileName, int numAnts, int iterations,
                           double pheromoneInfluence, double heuristicInfluence,
                           double evapFactor, double eliteFactor){
    this->type = type;
    this->fileName = fileName;
    this->numAnts = numAnts;
    this->iterations = iterations;
    this->pheromoneInfluence = pheromoneInfluence;
    this->heuristicInfluence = heuristicInfluence;
    this->evapFactor = evapFactor;
    this->eliteFactor = eliteFactor;
    
    this->problem = new Problem(this->fileName);
    
    initAnts();
}

/**
 *The constructor for ACS
 */

AntAlgorithm::AntAlgorithm(string type, string fileName, int numAnts, int iterations,
                           double pheromoneInfluence, double heuristicInfluence,
                           double evapFactor, double epsilon, double tao, double probability){
    this->type = type;
    this->fileName = fileName;
    this->numAnts = numAnts;
    this->iterations = iterations;
    this->pheromoneInfluence = pheromoneInfluence;
    this->heuristicInfluence = heuristicInfluence;
    this->evapFactor = evapFactor;
    this->epsilon = epsilon;
    this->tao = tao;
    this->probability = probability;
    
    this->problem = new Problem(this->fileName);
    
    initAnts();
}

/**
 *Initialize a vector of ants by adding each ant to the vector
 */

void AntAlgorithm::initAnts(){
    for (int i = 0; i < this->numAnts; i++){
        Ant* newAnt = new Ant();
        ants.push_back(newAnt);
    }
}

/**
 *The main function of the program
 */

void AntAlgorithm::run(){
    
}
