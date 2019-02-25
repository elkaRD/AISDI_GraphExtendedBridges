//
//  EN: The last project for Algorithms and Data Structures lectures at Warsaw University of Technology
//      Finding "extended bridges" in given graph
//
//  PL: Projekt AISDI (Algorytmy i Struktury Danych) PW WEiTI 18Z
//      Grafy - Wyszukiwanie mostow rozleglych
//
//      Copyright (C) 2019 Robert Dudzinski
//      Warsaw, January 2019
//
//      File: Tests.hpp
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
