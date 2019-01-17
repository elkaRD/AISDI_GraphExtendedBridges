//
//  main.cpp
//  aisdi_grafy
//
//  Created by Robert on 24/12/2018.
//  Copyright © 2018 Robert. All rights reserved.
//

#include <sstream>
#include "Graph.hpp"
using namespace std;

void CreateFullGraph(int n, string fileName)
{
    ofstream file;
    file.open(fileName.c_str());
    if (file.good())
    {
        file << n << endl;
        for (int i = 0; i < n-1; i++)
        {
            for (int j = i+1; j < n ; j++)
            {
                file << i << " " << j << endl;
            }
        }
    }
    else
    {
        cout << "ERROR creating a new file"<<endl;
    }
    
    file.close();
}

void onFoundSolution(unsigned int edgeBeg, unsigned int edgeEnd)
{
    cout << "Solution: " << edgeBeg << " " << edgeEnd << endl;
}

void CreateTests()
{
    for (int i = 1; i < 500;)
    {
        stringstream ss;
        ss<<i-1;
        string name = "data/data"+ss.str()+".txt";
        
        CreateFullGraph(i-1, name);
        i+=50;
    }
}

void PerformCorrectnessTests()
{
    
}

void PerformPerformanceTests()
{
    
}

int main(int argc, const char * argv[])
{
    //CreateFullGraph(100, "/Users/robert/studia/sem3/aisdi/aisdi_grafy/aisdi_grafy/data20.txt");
    //CreateTests();
    
    //return 0;
    
    //ofstream file;
    //file.open("results.txt");
    
    /*for (int i = 1; i < 500;)
    {
        clock_t begin = clock();
        
        Graph graph;
        //graph.SetOnFoundSolution(onFoundSolution);
        
        stringstream ss;
        ss<<i-1;
        string name = "data/data"+ss.str()+".txt";
        
        graph.Load(name);
        graph.Task();
        graph.CleanUp();
        
        clock_t end = clock();
        cout<<i<<"  "<<double(end-begin)/CLOCKS_PER_SEC<<endl;
        file<<i<<"  "<<double(end-begin)/CLOCKS_PER_SEC<<endl;
        i+=50;
    }*/
    
    Graph graph;
    //graph.Load("data2.txt");
    //graph.Load(cin);
    //cin >> graph;
    
    ifstream file;
    file.open("data2.txt");
    file >> graph;
    file.close();
    
    graph.SetOnFoundSolution(onFoundSolution);
    graph.Task();
    graph.CleanUp();
    
    //file.close();
    
    cout<<"End of the program" << endl;
    
    return 0;
}
