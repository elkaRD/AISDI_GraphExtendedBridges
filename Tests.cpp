//
//  Tests.cpp
//  aisdi_grafy
//
//  Copyright © 2019 Robert Dudzinski. All rights reserved.
//

#include "Tests.hpp"

using namespace std;

bool Contains(vector<pair<unsigned int, unsigned int> > &v, const unsigned int a, const unsigned int b)
{
    if (find(v.begin(), v.end(), pair<unsigned int, unsigned int>(a, b)) == v.end())
    {
        return find(v.begin(), v.end(), pair<unsigned int, unsigned int>(b, a)) != v.end();
    }
    return true;;
}

bool cTest1()
{
    stringstream ss;
    ss << " 4 \
            0 1 \
            1 2 \
            2 3 \
            3 0 \
            0 2";
    
    Graph graph;
    ss >> graph;
    vector<pair<unsigned int, unsigned int> > result = graph.Task();
    graph.CleanUp();
    
    if (result.size() != 1) return true;
    if (!Contains(result, 0, 2)) return true;
    
    return false;
}

bool cTest2()
{
    stringstream ss;
    ss << " 17 \
            0 1 \
            0 2 \
            1 3 \
            2 3 \
            3 4 \
            4 5 \
            5 6 \
            5 7 \
            6 8 \
            7 8 \
            4 9 \
            9 10 \
            9 11 \
            10 12 \
            11 12 \
            4 13 \
            13 14 \
            13 15 \
            14 16 \
            15 16";
    
    Graph graph;
    ss >> graph;
    vector<pair<unsigned int, unsigned int> > result = graph.Task();
    graph.CleanUp();
    
    if (result.size() != 12) return true;
    if (!Contains(result, 1, 3)) return true;
    if (!Contains(result, 2, 3)) return true;
    if (!Contains(result, 3, 4)) return true;
    if (!Contains(result, 4, 5)) return true;
    
    if (!Contains(result, 5, 6)) return true;
    if (!Contains(result, 5, 7)) return true;
    if (!Contains(result, 4, 9)) return true;
    if (!Contains(result, 9, 10)) return true;
    
    if (!Contains(result, 9, 11)) return true;
    if (!Contains(result, 4, 13)) return true;
    if (!Contains(result, 13, 14)) return true;
    if (!Contains(result, 13, 15)) return true;
    
    return false;
}

bool cTest3()
{
    Graph graph;
    graph.CreateK(20);
    vector<pair<unsigned int, unsigned int> > result = graph.Task();
    graph.CleanUp();
    
    if (result.size() != 0) return true;
    
    return false;
}

bool cTest4()
{
    stringstream ss;
    ss << "20";
    
    Graph graph;
    ss >> graph;
    vector<pair<unsigned int, unsigned int> > result = graph.Task();
    graph.CleanUp();
    
    if (result.size() != 0) return true;
    
    return false;
}

bool cTest5()
{
    Graph graph;
    vector<pair<unsigned int, unsigned int> > result = graph.Task();
    graph.CleanUp();
    
    if (result.size() != 0) return true;
    
    return false;
}

bool cTest6()
{
    Graph graph;
    graph.CreateP(5);
    vector<pair<unsigned int, unsigned int> > result = graph.Task();
    graph.CleanUp();
    
    if (result.size() != 2) return true;
    if (!Contains(result, 1, 2)) return true;
    if (!Contains(result, 2, 3)) return true;
    
    return false;
}

bool cTest7()
{
    Graph graph;
    graph.CreateC(15);
    vector<pair<unsigned int, unsigned int> > result = graph.Task();
    graph.CleanUp();
    
    if (result.size() != 0) return true;
    
    return false;
}

bool PerformCorrectnessTests()
{
    if (cTest1()) {cout << "test1 failed" << endl; return true;}
    if (cTest2()) {cout << "test2 failed" << endl; return true;}
    if (cTest3()) {cout << "test3 failed" << endl; return true;}
    if (cTest4()) {cout << "test4 failed" << endl; return true;}
    if (cTest5()) {cout << "test5 failed" << endl; return true;}
    if (cTest6()) {cout << "test6 failed" << endl; return true;}
    if (cTest7()) {cout << "test7 failed" << endl; return true;}
    
    return false;
}

void PerformPerformanceTests(unsigned int minV, unsigned int maxV, const unsigned int step)
{
    if (step == 0) return;
    if (maxV < minV) maxV = minV;
    
    Graph graph;
    
    while (minV <= maxV)
    {
        cout << "BEG PERFORMANCE TEST FOR " << minV << endl;
        
        graph.CreateK(minV);
        auto start = chrono::high_resolution_clock::now();
        
        graph.Task();
        
        auto finish = chrono::high_resolution_clock::now();
        std::chrono::duration<float> secs = finish - start;
        cout << "END PERFORMANCE TEST FOR " << minV << ":  " << secs.count() << endl;

        graph.CleanUp();
        minV += step;
    }
}
