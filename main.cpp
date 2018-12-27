//
//  main.cpp
//  aisdi_grafy
//
//  Created by Robert on 24/12/2018.
//  Copyright © 2018 Robert. All rights reserved.
//

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

int main(int argc, const char * argv[])
{
    //CreateFullGraph(100, "/Users/robert/studia/sem3/aisdi/aisdi_grafy/aisdi_grafy/data20.txt");
    
    Graph graph;
    graph.SetOnFoundSolution(onFoundSolution);
    graph.Load("/Users/robert/studia/sem3/aisdi/aisdi_grafy/aisdi_grafy/data.txt");
    graph.Task();
    graph.CleanUp();
    
    cout<<"End of the program" << endl;
    
    return 0;
}
