//
//  main.cpp
//  aisdi_grafy
//
//  Copyright © 2019 Robert Dudzinski. All rights reserved.
//

#include <sstream>
#include "Graph.hpp"
#include "Tests.hpp"
using namespace std;

void onFoundSolution(unsigned int edgeBeg, unsigned int edgeEnd)
{
    cout << "Solution: " << edgeBeg << " " << edgeEnd << endl;
}

int main(int argc, const char * argv[])
{
    if (PerformCorrectnessTests())
        cout << "FAILED TESTS" << endl;
    else
        cout << "PASSED TESTS" << endl;
    
    PerformPerformanceTests(50, 200, 50);
    
    Graph graph;

    //cin >> graph;
    
    ifstream file;
    file.open("data2.txt");
    file >> graph;
    file.close();
    
    graph.SetOnFoundSolution(onFoundSolution);
    graph.Task();
    graph.CleanUp();
    
    cout<<"End of the program" << endl;
    
    return 0;
}
