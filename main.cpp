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
//      File: main.cpp
//

// BUILDING PROJECT: 'g++ main.cpp Graph.cpp Tests.cpp -O3 -std=c++11'

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
        cout << endl << "FAILED CORRECTNESS TESTS" << endl << endl;
    else
        cout << endl << "PASSED CORRECTNESS TESTS" << endl << endl;
    
    //for the best results test a release version with enabled optimization (-O3)
    cout << "Testing performance using complete graphs" << endl;
    PerformPerformanceTests(50, 300, 50);
    
    cout << endl << "Resolving given graph" << endl;
    
    Graph graph;

    //cin >> graph;
    
    ifstream file;
    file.open("SampleGraphs/data3.txt");
    file >> graph;
    file.close();
    
    graph.SetOnFoundSolution(onFoundSolution);
    graph.Task();
    graph.CleanUp();
    
    cout<<"End of the program" << endl;
    
    return 0;
}
