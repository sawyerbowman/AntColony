//
//  EdgeUpdate.cpp
//  AntColony
//
//  Created by Sawyer Bowman on 4/2/15.
//  Copyright (c) 2015 Sawyer Bowman. All rights reserved.
//

#include "EdgeUpdate.h"

/**
 *Constructor for creating an edge update in an ant's delta tau summation
 */

EdgeUpdate::EdgeUpdate(int origin, int destination, double update){
    this->origin = origin;
    this->destination = destination;
    this->update = update;
}