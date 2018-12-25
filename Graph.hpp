//
//  Graph.hpp
//  aisdi_grafy
//
//  Created by Robert on 25/12/2018.
//  Copyright © 2018 Robert. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

struct Edge;
struct Vertex;

class GraphLoader
{
public:
    void Load(std::string fileName);
    
protected:
    virtual void onLoadedVertices(int n) = 0;
    virtual void onLoadedEdge(int b, int e) = 0;
};

struct Vertex
{
    Vertex(int i) : index(i), isRemoved(0), marker(nullptr)
    {
        
    }
    
    //    Vertex(int i, Edge *e) : index(i), isRemoved(0), marker(-1)
    //    {
    //        edges.push_back(e);
    //    }
    
    void AddEdge(Edge *e, Vertex *v)
    {
        edges.push_back(e);
        adjacents.push_back(v);
    }
    
    int index;
    int isRemoved;
    int *marker;
    
    std::vector<Edge*> edges;
    std::vector<Vertex*> adjacents;
};

struct Edge
{
    Edge(Vertex *b, Vertex *e) : beg(b), end(e)
    {
        beg->AddEdge(this, end);
        end->AddEdge(this, beg);
    }
    
    Vertex *beg;
    Vertex *end;
};

class Graph : public GraphLoader
{
public:
    void Task();
    void CleanUp();
    
private:
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;
    
    int markerCounter;
    
    void StartMarking(Edge *e);
    void Mark(Vertex *v, int *markerVal);
    
    void onLoadedVertices(int n);
    void onLoadedEdge(int b, int e);
};

#endif /* Graph_hpp */
