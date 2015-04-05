 ______     ______     ______     _____        __    __     ______    
/\  == \   /\  ___\   /\  __ \   /\  __-.     /\ "-./  \   /\  ___\   
\ \  __<   \ \  __\   \ \  __ \  \ \ \/\ \    \ \ \-./\ \  \ \  __\   
 \ \_\ \_\  \ \_____\  \ \_\ \_\  \ \____-     \ \_\ \ \_\  \ \_____\ 
  \/_/ /_/   \/_____/   \/_/\/_/   \/____/      \/_/  \/_/   \/_____/ 

Project Name:	Evolutionary Algorithms: Lab 2
Created by: 	Sawyer Bowman '15, David Needell '15, Phoebe Bumsted ’17, Ryan Barrett ’17
Email:			Sawyer:	sbowman@bowdoin.edu
			David:	dneedell@bowdoin.edu
			Phoebe:	pbumsted@bowdoin.edu
			Ryan:	rbarrett@bowdoin.edu

Date Created: 	March, 2015
Last Modified: 	April, 2015 
Version:		1.0
Language: 		C++

---------------------------------------------------------------------

DESCRIPTION:
This program compares two methods of Ant Colony Optimization (Ant Colony System and Elitist Ant System) for the Traveling Salesman Problem.

HOW TO RUN:
The user must pass the following parameters as command line arguments.

//SHARED ARGUMENTS
Type (string)			ex. EAS
File Name (string)		ex. pr1002.tsp
Number Ants (int)		ex. 10
Iterations (int)		ex. 100
Alpha (double)			ex. 1
Beta (double)			ex. 3
Rho (double)			ex. .1

//FOR EAS ONLY
Elitist Factor (double)		ex. 10

//FOR ACS ONLY
Epsilon (double)		ex. .1
q (double)			ex. .9
