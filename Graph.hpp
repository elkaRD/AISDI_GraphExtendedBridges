//
//  Graph.hpp
//  aisdi_grafy
//
//  Copyright © 2019 Robert Dudzinski. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <vector>
#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>

class GraphLoader
{
public:
    void CreateK(const unsigned int k);
    void CreateP(const unsigned int p);
    void CreateC(const unsigned int c);
    
protected:
    void Load(std::istream &input);
    
    virtual void onLoadedVertices(unsigned int n) = 0;
    virtual void onLoadedEdge(unsigned int b, unsigned int e) = 0;
};

class Graph : public GraphLoader
{
public:
    ~Graph();
    
    std::vector<std::pair<unsigned int, unsigned int> > Task();
    void CleanUp();
    
    void SetOnFoundSolution(std::function<void(unsigned int, unsigned int)> onSolution);
    size_t GetVerticesCount() const;
    size_t GetEdgesCount() const;
    
private:
    struct Edge;
    struct Vertex;
    
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;
    std::function<void(unsigned int ,unsigned int)> onFoundSolution;
    std::vector<std::pair<unsigned int, unsigned int> > solutions;
    
    void StartMarking(Edge *e);
    void Mark(Vertex *v);
    
    void onLoadedVertices(unsigned int n);
    void onLoadedEdge(unsigned int b, unsigned int e);
    
    size_t counter;

    struct Vertex
    {
        Vertex(unsigned int i) : index(i), isRemoved(0)
        {
        }
        
        void AddEdge(Edge *e, Vertex *v)
        {
            edges.push_back(e);
            adjacents.push_back(v);
        }
        
        unsigned int index;
        int isRemoved;
        
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
    
    friend std::istream& operator >> (std::istream &in, Graph &right);
};

std::istream& operator >> (std::istream &in, Graph &right);

#endif /* Graph_hpp */
