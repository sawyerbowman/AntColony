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
    this->map = new PheromoneMap(this->problem->getCities());
    
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
    this->map = new PheromoneMap(this->problem->getCities());
    
    initAnts();
}

/**
 *Initialize a vector of ants by adding each ant to the vector
 */

void AntAlgorithm::initAnts(){
    for (int i = 0; i < this->numAnts; i++){
        Ant* newAnt = new Ant(this->map, this->problem->getCities());
        ants.push_back(newAnt);
    }
}

/**
 *The main function of the program
 */

void AntAlgorithm::run(){
    for (int i = 0; i < this->iterations; i++){
        for (int a = 0; a < numAnts; a++){
            //clear the tour and build a new one
        }
        //Perform ACS
        if (this->type == "ACS"){
            for (Ant* currentAnt : this->ants){
                this->map->updatePheromones(currentAnt->getVisitedCities(),
                                            this->evapFactor);
            }
        }
        //Perform EAS
        else {
            this->map->eliteUpdatePheromones(findBestTour(), this->evapFactor,
                                             this->eliteFactor, this->bsf);
        }
    }
}

/**
 *A helper function to find the best tour so far
 */

vector<City*> AntAlgorithm::findBestTour(){
    this->bsf = this->ants[0]->getTourLength();
    vector<City*> bestTour = this->ants[0]->getVisitedCities();
    
    //Loop through all of the ants in our algorithm to find the best tour so far
    for (Ant* currentAnt : this->ants){
        if (currentAnt->getTourLength() < this->bsf){
            this->bsf = currentAnt->getTourLength();
            bestTour = currentAnt->getVisitedCities();
        }
    }
    
    return bestTour;
}


