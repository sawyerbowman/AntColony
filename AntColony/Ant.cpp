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
    /*
     *Don't delete from this vector, must keep all elements. The other vector
     *of cities (passed in) represents the vector we delete from.
     */
    vector<City*> allCities = cities;
    
    //Get the starting city
    int randCity = rand() % cities.size();
    visitedCities.push_back(cities[randCity]);
    cities.erase(cities.begin()+randCity);
    
    //get the pheromone map
    vector<vector<double>> pheroMap = pMap->getPheromoneMap();
    
    //loop through until all cities have been visited
    while (cities.size() > 0){
        //cout << cities.size() << endl;
        
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
                City* newCity = addCityOnMaxEdge(pheroMap, distances, beta, cities,
                                                 numOfStartCity);
                int newCityNum = newCity->getCityNum();
                //int newCityNum = startCity->getNearestCity();
                //City* newCity = allCities[newCityNum];
                
                this->visitedCities.push_back(newCity);
                this->tourLength += distances[numOfStartCity][newCityNum];
                
                //cout << newCityNum << endl;
                
                //remove city that was just added
                cities.erase(remove(cities.begin(), cities.end(), newCity), cities.end());
                
//                for (int i = 0; i < cities.size(); i++){
//                    cout << cities[i]->getCityNum() << endl;
//                }
                
                //wear out the pheromones on the edge traversed
                erasePheromones(numOfStartCity, newCity->getCityNum(), epsilon, pheroMap,
                                tauNaught, pMap);

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
                cout << "This is bad" << endl;
                etaNum = 0;
            }
            //else if(startCity->calcDistance(cities[i]) == 0){
            else if (distances[numOfStartCity][addCityNum] == 0){
                //if there are two, distinct cities that occupy the same location,
                //we automatically want to visit that city, so we will add that city
                //to our visited cities vector automatically and skip everything else!
                cout << "This is bad" << endl;
                this->visitedCities.push_back(cities[i]);
                sameLocation = true;
                break;
            }
            else {
                //etaNum = pow(startCity->calcDistance(cities[i]), -1*beta);
                etaNum = pow(1/distances[numOfStartCity][addCityNum], beta);
            }
            
            numerators.push_back(tauNum*etaNum);

            den += tauNum*etaNum;
        }
        
        if(!sameLocation){
            //Calculate probabilities between cities and determine which edge to take
            double randNextCity = (double) rand()/RAND_MAX;
            double edgeProbSum = 0;
            
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
                        erasePheromones(numOfStartCity, addCityNum, epsilon, pheroMap,
                                        tauNaught, pMap);
                    }
                    cities.erase(cities.begin()+i);
                    break;
                }
            }
        }
    }
}

/**
 *Erase pheromones on given edge
 */

void Ant::erasePheromones(int startCityNum, int addCityNum, double epsilon,
                          vector<vector<double>> pheroMap, double tauNaught,
                          PheromoneMap* pMap ){
    pheroMap[startCityNum][addCityNum] = (1-epsilon)*pheroMap[startCityNum][addCityNum]
                                        + epsilon*tauNaught;
    pMap->setPheromoneMap(pheroMap);
}

/**
 *If using the Ant Colony System, this will choose a city to add to the ant's
 *tour with a probability of q that represents the maximal edge of pheromone
 *times 1/edgedistance ^ Beta
 */

City* Ant::addCityOnMaxEdge(vector<vector<double>> pheroMap, vector<vector<double>> distances,
                           double beta, vector<City*> remainCities, int startCityNum){
    double bestEdge = 0;
    City* bestCity = nullptr;
    
    //Loop through remaining cities to determine next best city to add
    for (City* city : remainCities){
        int cityNum = city->getCityNum();
        
        //Add city immediately if distance is 0
        if (distances[startCityNum][cityNum] == 0){
            return city;
        }

        double newEdge = pheroMap[startCityNum][cityNum] *
                        pow((1/distances[startCityNum][cityNum]), beta);
        
        //Update best city if necessary
        if (newEdge > bestEdge){
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
