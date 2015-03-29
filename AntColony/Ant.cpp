//
//  Ant.cpp
//  AntColony
//
//  Created by Sawyer Bowman on 3/23/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include "Ant.h"
#include <math.h>


Ant::Ant(PheromoneMap pMap, vector<City> cities){
    addToVisitedCities(pMap, cities);
    tourLength = 0;
}


void Ant::addToVisitedCities(PheromoneMap pMap, vector<City> cities){
    
    const double k = 5;
    const double alpha = 7;
    
    //randomly select the ant's starting city
    int numCities = cities.size();
    int rand = rand() % numCities;
    visitedCities.push_Back(cities.at(rand));
    cities.erase(rand);
    
    //get the perhomone map
    vector<vector<double>> pheroMap = pMap.getPheromoneMap();
    
    
    //build the rest of the tour
    while(cities.size() > 0){
        int numOfStartCity = visitedCities.at(visitedCities.size()-1).getCityNum();
         vector<int> pheromoneProbabilities;
        //calculate the probability of visiting each of the remaining cities
        double totalOfNumerators = 0;
        
        for(int i = 0; i < cities.size(); i++){
            //get pheromone concentration for edge between the two cities in question
            double tau = pheroMap.at(numOfStartCity).at(cities.at(i).getCityNum());
            
            double numeratorProb = pow((tau+k), alpha);
            
            totalOfNumerators += numeratorProb;
            pheromoneProbabilities.push_back(numeratorProb);
        }
        
        //choose the next city based on probabilities
        double chooseCity = rand() % totalOfNumerators;
        bool chosen = false;
        double currentTotal = 0;
        int i = 0; //loop variable
        
        while(chosen == false){
            currentTotal += pheromoneProbabilities.at(i);
            if(currentTotal >= chooseCity){
                visitedCities.push_back(cities.at(i));
                cities.erase(i);
                chosen = true;
            }
            i++;
        }
        tourLength += visitedCities.at(visitedCities.size()-1).calcDistance(visitedCities.size()-2);
        
    }
}

void Ant::clearVisitedCities(){
    
}

