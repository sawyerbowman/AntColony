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
    cout << "Tao:           wearing away of pheromone in ACS (double)" << endl;
    cout << "q:             probability in ACS ant will choose best leg "
    " for next leg of tour it is constructing (double)" << endl;
}

/**
 *Parses the command line parameters and runs the particular algorithms
 */

int main(int argc, const char * argv[]) {
    srand( time( NULL ) );
    
    //If wrong number of params for both algorithms, offer instructions for both
    if (argc != 9 && argc != 11){
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
    else if (argc != 11 && type == ACS){
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
            
            eas.run();
        }
        else{
            double epsilon = stod(argv[8]);
            double tao = stod(argv[9]);
            double q = stod(argv[10]);
            
            //create ACS object and run
            AntAlgorithm acs = AntAlgorithm(type, fileName, ants, iterations, alpha, beta,
                                            rho, epsilon, tao, q);
            acs.run();
        }
    }
    
    
    cout << "DONE!" << endl;
}
