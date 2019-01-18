//
//  Graph.cpp
//  aisdi_grafy
//
//  Copyright © 2019 Robert Dudzinski. All rights reserved.
//

#include "Graph.hpp"

using namespace std;

void GraphLoader::Load(std::istream &input)
{
    try
    {
        int n;
        input >> n;
        
        onLoadedVertices(n);
        
        while (input)
        {
            int b=0, e=0;
            input >> b >> e;
            if (b < 0 || b >= n || e < 0 || e >= n || b == e)
            {
                if (!input) break;
                
                throw pair<unsigned int, unsigned int> (b, e);
            }
            onLoadedEdge(b, e);
        }
    }
    catch (pair<unsigned int, unsigned int> e)
    {
        cout << "Exception: Wrong input data " << e.first <<" "<<e.second<<"   aborting" << endl;
    }
    catch (exception e)
    {
        cout << "Unknown exception: " << e.what() << endl;
    }
}

void GraphLoader::CreateK(const unsigned int k)
{
    onLoadedVertices(k);
    
    for (unsigned int i = 0; i < k-1; ++i)
        for (unsigned int j = i+1; j < k; ++j)
            onLoadedEdge(i, j);
}

void GraphLoader::CreateP(const unsigned int p)
{
    onLoadedVertices(p);
    
    for (unsigned int i = 0; i < p-1; ++i)
        onLoadedEdge(i, i+1);
}

void GraphLoader::CreateC(const unsigned int c)
{
    onLoadedVertices(c);
    
    for (unsigned int i = 0; i < c-1; ++i)
        onLoadedEdge(i, i+1);
    
    onLoadedEdge(0, c-1);
}

vector<pair<unsigned int, unsigned int> > Graph::Task()
{
    solutions.clear();
    
    for (auto &it : edges)
        StartMarking(&it);
    
    return solutions;
}

void Graph::StartMarking(Edge *e)
{
    for (auto &it : vertices)
        it.isRemoved = 0;
    
    vertices[e->beg].isRemoved = 1;
    vertices[e->end].isRemoved = 1;
    
    counter = 0;
    
    for (const auto &it : vertices[e->beg].adjacents)
    {
        if (it != e->end)
        {
            Mark(it);
            break;
        }
    }
    
    if (counter == 0)
        for (const auto &it : vertices[e->end].adjacents)
        {
            if (it != e->beg)
            {
                Mark(it);
                break;
            }
        }
    
    
    if (counter != vertices.size() - 2)
    {
        if (onFoundSolution)
            onFoundSolution(vertices[e->beg].index, vertices[e->end].index);

        solutions.push_back(pair<unsigned int, unsigned int>(vertices[e->beg].index, vertices[e->end].index));
    }
}

void Graph::Mark(int v)
{
    //cout << "BEG: " << v << endl;
    
    vertices[v].isRemoved = 1;
    ++counter;
    
    //cout << "DEBUG: " << v << endl;
    
    for (const auto &it : vertices[v].adjacents)
        if (!vertices[it].isRemoved)
            Mark(it);
}

Graph::~Graph()
{
    CleanUp();
}

void Graph::CleanUp()
{
    //for (auto &it : vertices) delete it;
    //for (auto &it : edges) delete it;
    
    vertices.clear();
    edges.clear();
}

void Graph::onLoadedVertices(unsigned int n)
{
    CleanUp();
    
    vertices.reserve(n);
    
    for (int i = 0; i < n; ++i)
        vertices.push_back(Vertex(i));
}

void Graph::onLoadedEdge(unsigned int b, unsigned int e)
{
    edges.push_back(Edge(b, e, *this));
    //(--edges.end())->Set();
}

void Graph::SetOnFoundSolution(function<void(unsigned int, unsigned int)> onSolution)
{
    onFoundSolution = onSolution;
}

size_t Graph::GetVerticesCount() const
{
    return vertices.size();
}

size_t Graph::GetEdgesCount() const
{
    return edges.size();
}

std::istream& operator >> (std::istream &in, Graph &right)
{
    right.Load(in);
    return in;
}
