//
//  EdgeUpdate.h
//  AntColony
//
//  Created by Sawyer Bowman on 4/2/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#ifndef __AntColony__EdgeUpdate__
#define __AntColony__EdgeUpdate__

#include <stdio.h>

using namespace std;

class EdgeUpdate{
public:
    //Constructor
    EdgeUpdate(int origin, int destination, double update);
    
    //Getters
    int getOrigin() { return this->origin; }
    int getDestination() { return this->destination; }
    double getUpdate() { return this->update; }
    
private:
    int origin;
    int destination;
    double update;
    
};

#endif /* defined(__AntColony__EdgeUpdate__) */
