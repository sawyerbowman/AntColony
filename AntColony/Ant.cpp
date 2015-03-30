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
 *
 */

void Ant::createTour(PheromoneMap* pMap, vector<City*> cities, double alpha,
                     double beta){
    //Get the starting city
    int randCity = rand() % cities.size();
    visitedCities.push_back(cities[randCity]);
    cities.erase(cities.begin()+randCity);
    
    //get the perhomone map
    vector<vector<double>> pheroMap = pMap->getPheromoneMap();
    
    while (cities.size() > 0){
        vector<double> edgeProbs;
        vector<double> numerators;
        
        double tauDen = 0;
        double etaDen = 0;
        
        City* startCity = visitedCities[visitedCities.size()-1];
        int numOfStartCity = startCity->getCityNum();
        
        for(int i = 0; i < cities.size(); i++){
            
            //get pheromone concentration for edge between the two cities in question
            if (i != numOfStartCity){
                double tau = pheroMap[numOfStartCity-1][cities[i]->getCityNum()-1];
            
                double tauNum = pow((tau), alpha);
                double etaNum = pow(startCity->calcDistance(cities[i]), -1*beta);
                numerators.push_back(tauNum*etaNum);
                
                tauDen += tauNum;
                etaDen += etaNum;
            }
        }
        
        //calculate probabilities between cities
        for (int i = 0; i < numerators.size(); i++){
            edgeProbs.push_back(numerators[i]/(tauDen*etaDen));
        }
        
        double randNextCity = (double) rand()/RAND_MAX;
        double edgeProbSum = 0;
        for (int i = 0; i < edgeProbs.size(); i++){
            edgeProbSum += edgeProbs[i];
            if (edgeProbSum > randNextCity){
                this->visitedCities.push_back(cities[i]);
                this->tourLength += startCity->calcDistance(cities[i]);
                cities.erase(cities.begin()+i);
                break;
            }
        }
    }
}

/**
 *
 */

void Ant::clearVisitedCities(){
    this->visitedCities.clear();
}
