//
//  main.cpp
//  AntColony
//
//  Created by Sawyer Bowman on 3/23/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include <stdio.h>
#include "AntAlgorithm.h"
#include <iostream>
#include <fstream>

using namespace std;

const string EAS = "EAS";
const string ACS = "ACS";

const int reps = 5;
const int iterations = 100;
const int numAnts[] = {10, 30};
const double elitestFactor[] = {10, 30};
const double alpha[] = {1, 2};
const double beta[] = {3, 5};
const double rho[] = {.1, .3};
const double qNaught[] = {.7, .9};

/**
 *Prints out the instructions for parameter entry on the command line for EAS
 */

void printEASWarnings(){
    cout << "Please enter the correct number of parameters for the elitist ant "
    "system algorithm!" << endl;
    cout << "Type:          Ant Colony System (ACS) or Elitist Ant System "
    "(EAS) (string)" << endl;
    cout << "fileName:      the name of the file (string)" << endl;
    cout << "Ants:          the number of ants (int)" << endl;
    cout << "Iterations:    the number of iterations ex. 1000 (int)" << endl;
    cout << "Alpha:         the degree of influence of the pheromone "
    "component (double)" << endl;
    cout << "Beta:          the degree of influence of the heuristic "
    "component (double)" << endl;
    cout << "Rho:           the pheromone evaporation factor (double)"
    << endl;
    cout << "e:             the elitism factor (double)" << endl;
}

/**
 *Prints out the instructions for parameter entry on the command line for ACS
 */

void printACSWarnings(){
    cout << "Please enter the correct number of parameters for the ant colony "
    "system algorithm!" << endl;
    cout << "Type:          Ant Colony System (ACS) or Elitist Ant System "
    "(EAS) (string)" << endl;
    cout << "fileName:      the name of the file (string)" << endl;
    cout << "Ants:          the number of ants (int)" << endl;
    cout << "Iterations:    the number of iterations ex. 1000 (int)" << endl;
    cout << "Alpha:         the degree of influence of the pheromone "
    "component (double)" << endl;
    cout << "Beta:          the degree of influence of the heuristic "
    "component (double)" << endl;
    cout << "Rho:           the pheromone evaporation factor (double)"
    << endl;
    cout << "Epsilon:       wearing away of pheromone in ACS (double)" << endl;
    cout << "q:             probability in ACS ant will choose best leg "
    " for next leg of tour it is constructing (double)" << endl;
}

/**
 *Saves output into csv file
 */

void saveResultsACS(string problemName, int numAnts, double alpha, double beta, double rho){
    ofstream csvFile;
    csvFile.open("/Users/sawyerbowman/Desktop/acs_results", std::ios_base::app);
    
    csvFile << problemName << "," << numAnts << "," << alpha << "," << beta << "," <<
    rho << endl;
    
    csvFile.close();
}

/**
 *Saves output into csv file
 */

void saveResultsEAS(string problemName, int numAnts, double alpha, double beta, double rho){
    ofstream csvFile;
    csvFile.open("/Users/sawyerbowman/Desktop/eas_results", std::ios_base::app);
    
    csvFile << problemName << "," << numAnts << "," << alpha << "," << beta << "," <<
    rho << endl;
    
    csvFile.close();
}

/**
 *Testing loop
 */

void testing(){
    for (int alph = 0; alph < 2; alph++){
        for (int bet = 0; bet < 2; bet++){
            for (int rh = 0; rh < 2; rh++){
                for (int r = 0; r < reps; r++){
                    //run ACS
                    AntAlgorithm* alg = new AntAlgorithm("ACS", "filename", numAnts[0], iterations, alpha[alph], beta[bet], rho[rh], .1, .9);
                    alg->run(0);
                    
                    //write ACS results
                    saveResultsACS("fileName", numAnts[0], alpha[alph], beta[bet], rho[rh]);
                    
                    
                    //run EAS
                    alg = new AntAlgorithm("EAS", "filename", numAnts[0], iterations, alpha[alph], beta[bet], rho[rh], elitestFactor[0]);
                    alg->run(0);
                    
                    //write EAS results
                    saveResultsEAS("fileName", numAnts[0], alpha[alph], beta[bet], rho[rh]);
                }
            }
        }
    }
}

/**
 *Parses the command line parameters and runs the particular algorithms
 */

int main(int argc, const char * argv[]) {
    srand( time( NULL ) );
    
    //If wrong number of params for both algorithms, offer instructions for both
    if (argc != 9 && argc != 10){
        printEASWarnings();
        
        cout << "" << endl;
        cout << "OR..." << endl;
        cout << "" << endl;
        
        printACSWarnings();
    }
    
    string type = argv[1];
    
    //Print warnings for wrong number of parameters for EAS
    if (argc != 9 && type == EAS) {
        printEASWarnings();
    }
    
    //Print warnings for wrong number of parameters for ACS
    else if (argc != 10 && type == ACS){
        printACSWarnings();
    }
    else {
        /*
         *Parse the shared parameters between Elitist Ant System and Ant Colony
         *System
         */
        string fileName = argv[2];
        int ants = stoi(argv[3]);
        int iterations = stoi(argv[4]);
        double alpha = stod(argv[5]);
        double beta = stod(argv[6]);
        double rho = stod(argv[7]);
        
        if (type == EAS){
            double e = stod(argv[8]);
            
            //create EAS object and run
            AntAlgorithm eas = AntAlgorithm(type, fileName, ants, iterations, alpha, beta,
                                            rho, e);
            
            eas.run(0);
        }
        else{
            double epsilon = stod(argv[8]);
            double q = stod(argv[9]);
            
            //create ACS object and run
            AntAlgorithm acs = AntAlgorithm(type, fileName, ants, iterations, alpha, beta,
                                            rho, epsilon, q);
            acs.run(0);
        }
    }
    
    
    cout << "DONE!" << endl;
}
