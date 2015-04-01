//
//  Ant.cpp
//  AntColony
//
//  Created by Sawyer Bowman on 3/23/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include "Ant.h"

/**
 *
 */

Ant::Ant(){
    tourLength = 0;
}

/**
 *Creates a tour by first selecting a random city, and then computing probabilities
 *for each edge to an unvisited city from the last city added to the ant's tour.
 */

void Ant::createTour(PheromoneMap* pMap, vector<City*> cities, double alpha,
                     double beta, vector<vector<double>> distances){
    //Get the starting city
    int randCity = rand() % cities.size();
    visitedCities.push_back(cities[randCity]);
    cities.erase(cities.begin()+randCity);
    
    //get the perhomone map
    vector<vector<double>> pheroMap = pMap->getPheromoneMap();
    
    while (cities.size() > 0){
        vector<double> edgeProbs;
        vector<double> numerators;

        double den = 0;
        
        City* startCity = visitedCities[visitedCities.size()-1];
        int numOfStartCity = startCity->getCityNum();
        
        for(int i = 0; i < cities.size(); i++){
            //get pheromone concentration for edge between the two cities in question
            double tau = pheroMap[numOfStartCity][cities[i]->getCityNum()];
        
            double tauNum = pow((tau), alpha);
            double etaNum = 0;
            if (startCity->getCityNum() == cities[i]->getCityNum()){
                etaNum = 0;
            }
            //else if(startCity->calcDistance(cities[i]) == 0){
            else if (distances[startCity->getCityNum()][cities[i]->getCityNum()] == 0){
                //if there are two, distinct cities that occupy the same location,
                //we automatically want to visit that city, so we will add that city
                //to our visited cities vector automatically and skip everything else!
            }
            else {
                //etaNum = pow(startCity->calcDistance(cities[i]), -1*beta);
                etaNum = pow(distances[startCity->getCityNum()][cities[i]->getCityNum()], -1*beta);
            }
            
            numerators.push_back(tauNum*etaNum);

            den += tauNum*etaNum;
        }
        
        double randNextCity = (double) rand()/RAND_MAX;
        double edgeProbSum = 0;
        
        //calculate probabilities between cities and determine which edge to take
        for (int i = 0; i < numerators.size(); i++){
            //in first run, everything will be 0, so divide equally between cities
            if (den == 0){
                edgeProbs.push_back((double)1/numerators.size());
            }
            else {
                edgeProbs.push_back(numerators[i]/(den));
            }
            edgeProbSum += edgeProbs[i];
            if (edgeProbSum > randNextCity){
                this->visitedCities.push_back(cities[i]);
                //this->tourLength += startCity->calcDistance(cities[i]);
                this->tourLength += distances[startCity->getCityNum()][cities[i]->getCityNum()];
                cities.erase(cities.begin()+i);
                break;
            }
        }
    }
    int x = 0;
}

/**
 *Clears a single ant's tour and tourlength, effectively allowing it to restart
 *without having to generate another ant
 */

void Ant::clearVisitedCitiesAndTour(){
    this->visitedCities.clear();
    this->tourLength = 0;
}
