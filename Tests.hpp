//
//  Tests.hpp
//  
//
//  Created by Robert Dudziński on 17/01/2019.
//

#ifndef Tests_hpp
#define Tests_hpp

#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "Graph.hpp"

bool PerformCorrectnessTests();
void PerformPerformanceTests(unsigned int minV = 10, unsigned int maxV = 150, const unsigned int step = 10);

#endif /* Tests_hpp */
