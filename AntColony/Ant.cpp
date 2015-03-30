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

Ant::Ant(PheromoneMap* pMap, vector<City*> cities){
    addToVisitedCities(pMap, cities);
    tourLength = 0;
}

/**
 *
 */

void Ant::addToVisitedCities(PheromoneMap* pMap, vector<City*> cities){
    
    const double k = 5;
    const double alpha = 7;
    
    //randomly select the ant's starting city
    int numCities = (int) cities.size();
    int randCity = rand() % numCities;
    visitedCities.push_back(cities[randCity]);
    cities.erase(cities.begin()+randCity);
    
    //get the perhomone map
    vector<vector<double>> pheroMap = pMap->getPheromoneMap();
    
    double totalOfNumerators = 1;
    
    //build the rest of the tour
    while(cities.size() > 0){
        int numOfStartCity = visitedCities[visitedCities.size()-1]->getCityNum();
        vector<int> pheromoneProbabilities;
        //calculate the probability of visiting each of the remaining cities
        
        for(int i = 0; i < cities.size(); i++){
            //get pheromone concentration for edge between the two cities in question
            double tau = pheroMap[numOfStartCity][cities[i]->getCityNum()];
            
            double numeratorProb = pow((tau+k), alpha);
            
            totalOfNumerators += numeratorProb;
            pheromoneProbabilities.push_back(numeratorProb);
        }
        
        //choose the next city based on probabilities
        double chooseCity = rand() % 2;
        
        bool chosen = false;
        double currentTotal = 0;
        int i = 0; //loop variable
        
        while(chosen == false){
            currentTotal += pheromoneProbabilities[i];
            if(currentTotal >= chooseCity){
                visitedCities.push_back(cities[i]);
                cities.erase(cities.begin()+i);
                chosen = true;
            }
            i++;
        }
        tourLength += visitedCities[visitedCities.size()-1]->calcDistance(visitedCities[visitedCities.size()-2]);
        
    }
}

/**
 *
 */

void Ant::clearVisitedCities(){
    
}
