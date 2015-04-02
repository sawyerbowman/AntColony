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
                           double alpha, double beta,
                           double evapFactor, double eliteFactor){
    this->type = type;
    this->fileName = fileName;
    this->numAnts = numAnts;
    this->iterations = iterations;
    this->alpha = alpha;
    this->beta = beta;
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
                           double alpha, double beta,
                           double evapFactor, double epsilon, double tao, double probability){
    this->type = type;
    this->fileName = fileName;
    this->numAnts = numAnts;
    this->iterations = iterations;
    this->alpha = alpha;
    this->beta = beta;
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
        Ant* newAnt = new Ant();
        ants.push_back(newAnt);
    }
}

/**
 *A function to build a tour through threads (each ant gets its own thread
 */
void buildTour(AntAlgorithm* data, Ant* currentAnt){
    //Clear the existing tour and build a new one for each ant
    currentAnt->clearVisitedCitiesAndTour();
    currentAnt->createTour(data->getMap(), data->getProblem()->getCities(), data->getAlpha(), data->getBeta(), data->getProblem()->getCityDistances(), data->getType(), data->getEpsilon(), data->getTaoNaught());
}

/**
 *The main function of the program
 */

void AntAlgorithm::run(){
    double globalBestDist = RAND_MAX;
    
    for (int i = 0; i < this->iterations; i++){
        
//        //Use threads to build a tour for each ant
//        std::thread threads[NUM_THREADS];
//        
//        /*
//         *initialize and run the thread passing in appropriate data
//         *NOTE: #ants must equal #threads!!!
//         */
//        for (int t = 0; t < NUM_THREADS; t++) {
//            Ant* currentAnt = this->ants[t];
//            threads[t] = std::thread(buildTour, this, currentAnt);
//        }
//        
//        /*
//         *make the main thread wait for each of these threads to complete before
//         *moving on
//         */
//        for (int t=0; t < NUM_THREADS; t++){
//            threads[t].join();
//        }
        
        //Clear the existing tour and build a new one for each ant
        for (Ant* currentAnt : this->ants){
            currentAnt->clearVisitedCitiesAndTour();
            currentAnt->createTour(this->map, this->problem->getCities(), this->alpha,
                                   this->beta, this->problem->getCityDistances(),
                                   this->type, this->epsilon, this->tao);
        }
        
        //Update the pheromone map based on tours constructed by ants
        vector<City*> bestTour = findBestTour();
        updatePheromones(bestTour, this->type);
        cout << "Best so far: " << this->bsf << endl;
        
        //Check if new global best found
        if (this->bsf < globalBestDist){
            globalBestDist = this->bsf;
        }
    }
    
    cout << "Best Tour Distance: " << globalBestDist << endl;
    exit(1);
}

/**
 *A helper function to find the best tour so far
 */

vector<City*> AntAlgorithm::findBestTour(){
    //Initialize the best tour as the first ant's tour
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

/**
 *Updates the pheromone map by first applying the evaporation factor, applying
 *a special update to edges within the best tour, and finally updating pheromones
 *on each edge present in all ants' tours.
 */

void AntAlgorithm::updatePheromones(vector<City*> bestTour, string type){
    //First update all pheromones by the (1-rho)*tau decremental factor.
    vector<vector<double>> pMap = this->map->getPheromoneMap();
    
    for(int i = 0; i < pMap.size(); i++){
        for(int j = 0; j < pMap.size(); j++){
            //update by the evaporation factor
            pMap[i][j] = (1 - evapFactor)*pMap[i][j];
        }
    }
    
    //Then update the pheromones by the elitist delta tau.
    for(int i = 0; i < bestTour.size()-1; i++){
        int index1 = bestTour[i]->getCityNum();
        int index2 = bestTour[i+1]->getCityNum();
        
        if(type == "EAS"){
            pMap[index1][index2] += this->eliteFactor/this->bsf;
            pMap[index2][index1] += this->eliteFactor/this->bsf;
            
        }
        else{
            pMap[index1][index2] += this->evapFactor/this->bsf;
            pMap[index2][index1] += this->evapFactor/this->bsf;
            
        }
    }
    
    if(type == "EAS"){
        //Next update the pheromones by the delta tau summation.
        for(int a = 0; a < this->ants.size(); a++){
            vector<City*> curTour = this->ants[a]->getVisitedCities();
        
            for(int b = 0; b < curTour.size()-1; b++){
                //Update the appropriate edges in the Pheromone map that corresponds
                //to the edge between the jth and jth + 1 (and vice versa) city of
                //that ant's tour. Sum it to the current value to get the delta tau summation.
                pMap[curTour[b]->getCityNum()][curTour[b+1]->getCityNum()] += 1/this->ants[a]->getTourLength();
                pMap[curTour[b+1]->getCityNum()][curTour[b]->getCityNum()] += 1/this->ants[a]->getTourLength();
            }
        }
    }
    
    this->map->setPheromoneMap(pMap);
}

