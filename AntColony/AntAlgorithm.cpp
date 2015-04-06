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
    this->tauNaught = 0;
    this->q = 0;
    
    this->problem = new Problem(this->fileName);
    this->map = new PheromoneMap(this->problem->getCities(), PHER_INIT);
    
    initAnts();
}

/**
 *The constructor for ACS
 */

AntAlgorithm::AntAlgorithm(string type, string fileName, int numAnts, int iterations,
                           double alpha, double beta,
                           double evapFactor, double epsilon, double q){
    this->type = type;
    this->fileName = fileName;
    this->numAnts = numAnts;
    this->iterations = iterations;
    this->alpha = alpha;
    this->beta = beta;
    this->evapFactor = evapFactor;
    this->epsilon = epsilon;
    this->q = q;
    
    this->problem = new Problem(this->fileName);
    calcTauNaught();
    this->map = new PheromoneMap(this->problem->getCities(), this->tauNaught);
    
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
void buildTour(AntAlgorithm* data, vector<Ant*> threadAnts){
    //Clear the existing tour and build a new one for each ant
    for (Ant* currentAnt : threadAnts){
        currentAnt->clearVisitedCitiesAndTour();
        currentAnt->createTour(data->getMap(), data->getProblem()->getCities(), data->getAlpha(),
                               data->getBeta(), data->getProblem()->getCityDistances(),
                               data->getType(), data->getEpsilon(), data->getTauNaught(), data->getQ());
    }
}

/**
 *
 */

void AntAlgorithm::calcTauNaught(){
    vector<City*> greedyTour = getGreedyTour();
    //calculate length of greedyTour
    double greedyLength = 0;
    for(int i = 0; i < greedyTour.size()-1; i++){
        greedyLength += greedyTour[i]->calcDistance(greedyTour[i+1]);
    }
    
    this->tauNaught = 1/(greedyLength*this->numAnts);
}

/**
 *The main function of the program
 */

double AntAlgorithm::run(int problemNum){
    double globalBestDist = RAND_MAX;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    //clock_t start = clock();
    
    for (int i = 0; i < this->iterations; i++){
        
        runThreads();
        
//        //Clear the existing tour and build a new one for each ant
//        for (Ant* currentAnt : this->ants){
//            currentAnt->clearVisitedCitiesAndTour();
//            currentAnt->createTour(this->getMap(), this->getProblem()->getCities(), this->getAlpha(),
//                                   this->getBeta(), this->getProblem()->getCityDistances(),
//                                   this->getType(), this->getEpsilon(), this->getTauNaught(), this->getQ());
//        }
        
        //Update the pheromone map based on tours constructed by ants
        vector<City*> bestTour = findBestTour();
        updatePheromones(bestTour, this->type);
        //cout << "Best so far: " << this->bsf << endl;
        
        //Check if new global best found
        if (this->bsf < globalBestDist){
            globalBestDist = this->bsf;
        }
        
        //Break out if it's time or the algorithm found a near optimal tour length
        gettimeofday(&end, NULL);
        double time = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        //double time = (double)(clock() - start)/CLOCKS_PER_SEC;
        //cout << time << endl;
        if (time > maxTime){ // || this->bsf <= 1.05*optimals[problemNum]){
            cout << "Iterations taken: " << i << "." << endl;
            break;
        }
    }
    
    cout << "Best Tour Distance: " << globalBestDist << endl;
    //exit(1);
    return globalBestDist;
}

/**
 *Responsible for initializing threads. For each ant, a thread builds a tour and computes
 *a vector of edge updates for that tour that will be used in the update of the
 *pheromone map.
 */

void AntAlgorithm::runThreads(){
    //Use threads to build a tour for each ant
    thread threads[NUM_THREADS];
    
    //divide into four vectors of approximately equal length
    vector<vector<Ant*> > allAnts;
    
    if (this->numAnts == 10){
        vector<Ant*> threadOneAnts(this->ants.begin(), this->ants.begin()+3);
        allAnts.push_back(threadOneAnts);
        vector<Ant*> threadTwoAnts(this->ants.begin()+3, this->ants.begin()+6);
        allAnts.push_back(threadTwoAnts);
        vector<Ant*> threadThreeAnts(this->ants.begin()+6, this->ants.begin()+8);
        allAnts.push_back(threadThreeAnts);
        vector<Ant*> threadFourAnts(this->ants.begin()+8, this->ants.begin()+10);
        allAnts.push_back(threadFourAnts);
    }
    else if (this->numAnts == 30) {
        vector<Ant*> threadOneAnts(this->ants.begin(), this->ants.begin()+8);
        allAnts.push_back(threadOneAnts);
        vector<Ant*> threadTwoAnts(this->ants.begin()+8, this->ants.begin()+16);
        allAnts.push_back(threadTwoAnts);
        vector<Ant*> threadThreeAnts(this->ants.begin()+16, this->ants.begin()+23);
        allAnts.push_back(threadThreeAnts);
        vector<Ant*> threadFourAnts(this->ants.begin()+23, this->ants.begin()+30);
        allAnts.push_back(threadFourAnts);
    }
    
    /*
     *Initialize and run the threads in the background. NOTE: the number
     *of threads needs to be the same as the number of ants
     */
    for (int t = 0; t < NUM_THREADS; t++) {
        //Ant* currentAnt = this->ants[t];
        threads[t] = thread(buildTour, this, allAnts[t]);
    }
    
    /*
     *make the main thread wait for each of these threads to complete before
     *moving on
     */
    for (int t=0; t < NUM_THREADS; t++){
        threads[t].join();
    }
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
    vector<vector<double> > pMap = this->map->getPheromoneMap();
    
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
            double pherUpdate = this->eliteFactor/this->bsf;
            pMap[index1][index2] += pherUpdate;
            pMap[index2][index1] += pherUpdate;
        }
        else{
            double pherUpdate = this->evapFactor/this->bsf;
            pMap[index1][index2] += pherUpdate;
            pMap[index2][index1] += pherUpdate;
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
                double pherUpdate = 1/this->ants[a]->getTourLength();
                pMap[curTour[b]->getCityNum()][curTour[b+1]->getCityNum()] += pherUpdate;
                pMap[curTour[b+1]->getCityNum()][curTour[b]->getCityNum()] += pherUpdate;
            }
        }
    }
    
    this->map->setPheromoneMap(pMap);
}

/**
 *
 */

vector<City*> AntAlgorithm::getGreedyTour(){
    vector<City*> problemCities = this->problem->getCities();
    vector<City*> visitedCities;
    int randCity = rand() % problemCities.size();
    
    //Add the first random city to our visitedCities vector.
    visitedCities.push_back(problemCities[randCity]);
    //Delete the city from our problemCities vector.
    problemCities.erase(problemCities.begin() + randCity);
    
    //Next we want to greedily add cities.
    while(problemCities.size() > 0){
        City* startCity = visitedCities[visitedCities.size()-1];
        
        City* bestCity = nullptr;
        double bestCityDist = RAND_MAX/1.0;
        int bestIndex = 0;
        
        //Find the closest city from startCity
        for(int i = 0; i < problemCities.size(); i++){
            double newDistance = startCity->calcDistance(problemCities[i]);
            if(newDistance < bestCityDist){
                bestCityDist = newDistance;
                bestCity = problemCities[i];
                bestIndex = i;
            }
        }
        visitedCities.push_back(bestCity);
        problemCities.erase(problemCities.begin() + bestIndex);
    }
    return visitedCities;
}

