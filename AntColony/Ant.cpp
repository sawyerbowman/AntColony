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
                     double beta, vector<vector<double>> distances, string
                     type, double epsilon, double tauNaught, double q){
    //Get the starting city
    int randCity = rand() % cities.size();
    visitedCities.push_back(cities[randCity]);
    cities.erase(cities.begin()+randCity);
    
    //get the perhomone map
    vector<vector<double>> pheroMap = pMap->getPheromoneMap();
    
    while (cities.size() > 0){
        vector<double> edgeProbs;
        vector<double> numerators;
        
        bool sameLocation = false;

        double den = 0;
        
        City* startCity = visitedCities[visitedCities.size()-1];
        int numOfStartCity = startCity->getCityNum();
        
        if (type == "ACS"){
            double randProb = (double) rand()/RAND_MAX;
            if (q > randProb){
                //add city that will maximize pheromone * 1/distance to beta
                this->visitedCities.push_back(addCityOnMaxEdge(pheroMap, distances,
                                                               beta, cities, numOfStartCity));
                continue;
            }
        }
        
        for(int i = 0; i < cities.size(); i++){
            int addCityNum = cities[i]->getCityNum();
            
            //get pheromone concentration for edge between the two cities in question
            double tau = pheroMap[numOfStartCity][addCityNum];
        
            double tauNum = pow((tau), alpha);
            double etaNum = 0;
            if (numOfStartCity == addCityNum){
                etaNum = 0;
            }
            //else if(startCity->calcDistance(cities[i]) == 0){
            else if (distances[numOfStartCity][addCityNum] == 0){
                //if there are two, distinct cities that occupy the same location,
                //we automatically want to visit that city, so we will add that city
                //to our visited cities vector automatically and skip everything else!
                
                this->visitedCities.push_back(cities[i]);
                sameLocation = true;
                break;
            }
            else {
                //etaNum = pow(startCity->calcDistance(cities[i]), -1*beta);
                etaNum = pow(distances[numOfStartCity][addCityNum], -1*beta);
            }
            
            numerators.push_back(tauNum*etaNum);

            den += tauNum*etaNum;
        }
        
        double randNextCity = (double) rand()/RAND_MAX;
        double edgeProbSum = 0;
        
        if(!sameLocation){
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
                    int addCityNum = cities[i]->getCityNum();
                    
                    this->visitedCities.push_back(cities[i]);
                    //this->tourLength += startCity->calcDistance(cities[i]);
                    this->tourLength += distances[numOfStartCity][addCityNum];
                    if(type == "ACS"){
                        pheroMap[numOfStartCity][addCityNum] =
                        (1-epsilon)*pheroMap[numOfStartCity][addCityNum] +
                        epsilon*tauNaught;
                        pMap->setPheromoneMap(pheroMap);
                    }
                    cities.erase(cities.begin()+i);
                    break;
                }
            }
        }
    }
}

/**
 *If using the Ant Colony System, this will choose a city to add to the ant's
 *tour with a probability of q that represents the maximal edge of pheromone
 *times 1/edgedistance ^ Beta
 */

City* Ant::addCityOnMaxEdge(vector<vector<double>> pheroMap, vector<vector<double>> distances,
                           double beta, vector<City*> remainCities, int startCityNum){
    double bestEdge = RAND_MAX;
    City* bestCity = remainCities[0];
    
    //Loop through remaining cities to determine next best city to add
    for (City* city : remainCities){
        int cityNum = city->getCityNum();
        
        //Add city immediately if distance is 0
        if (distances[startCityNum][cityNum] == 0){
            return city;
        }
        
        //TODO: could use some form of dynamic programming here so as not to recalc edges
        double newEdge = pheroMap[startCityNum][cityNum] *
                        pow((1/distances[startCityNum][cityNum]), beta);
        
        //Update best city if necessary
        if (newEdge < bestEdge){
            bestEdge = newEdge;
            bestCity = city;
        }
    }
    return bestCity;
}

/**
 *Clears a single ant's tour and tourlength, effectively allowing it to restart
 *without having to generate another ant
 */

void Ant::clearVisitedCitiesAndTour(){
    this->visitedCities.clear();
    this->tourLength = 0;
}
