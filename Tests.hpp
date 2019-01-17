//
//  Tests.hpp
//  aisdi_grafy
//
//  Copyright © 2019 Robert Dudzinski. All rights reserved.
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
