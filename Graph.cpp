//
//  Graph.cpp
//  aisdi_grafy
//
//  Created by Robert on 25/12/2018.
//  Copyright © 2018 Robert. All rights reserved.
//

#include "Graph.hpp"

using namespace std;

void GraphLoader::Load(string fileName)
{
    int debug1;
    int debug2;
    
    try
    {
        ifstream file;
        file.open(fileName.c_str());
        if (file.good())
        {
            int n;
            file >> n;
            
            onLoadedVertices(n);
            
            while (!file.eof())
            {
                int b=0, e=0;
                file >> b >> e;
                if (b < 0 || b >= n || e < 0 || e >= n || b == e)
                {
                    debug1 = b;
                    debug2 = e;
                    throw std::string("wrong input data: ");
                }
                //edges.push_back(new Edge(vertices[b], vertices[e]));
                onLoadedEdge(b, e);
                cout<<"Added edgee: "<<b<<" "<<e<<endl;
                //TODO: fix problem with loading ethe last line
            }
            
        }
        else throw "could not open the file " + fileName;
        file.close();
    }
    catch (std::string e)
    {
        cout << "Exception: " << e <<" "<<debug1<<" "<<debug2<< endl;
        //file.close()
    }
    catch (exception e)
    {
        cout << "Unknown exception: " << e.what() << endl;
    }
}

vector<pair<unsigned int, unsigned int> > Graph::Task()
{
    solutions.clear();
    size_t edgesCount = edges.size();
    
    for (int i = 0; i < edgesCount; i++)
        StartMarking(edges[i]);
    
    return solutions;
}

void Graph::StartMarking(Edge *e)
{
    e->beg->isRemoved = 1;
    e->end->isRemoved = 1;
     
    for (auto it : vertices)
        it->marker = nullptr;
    
    unordered_set<Vertex*> elems;
    for (auto it : e->beg->adjacents)
    {
        if (it != e->end)
            elems.insert(it);
    }
    for (auto it : e->end->adjacents)
    {
        if (it != e->beg)
            elems.insert(it);
    }
    
    size_t markerCounter = elems.size();
    
    int markerIndex = 0;
    int *markerVal[markerCounter];
    for (auto it : elems)
    {
        markerVal[markerIndex] = new int;
        *markerVal[markerIndex] = markerIndex+1;

        Mark(it, markerVal[markerIndex++]);
    }
    
    bool isSolution = false;
    for (int j = 0; j < markerCounter; ++j)
    {
        if (*markerVal[j] != 1) isSolution = true;
        
        delete markerVal[j];
    }
    
    if (isSolution)
    {
        if (onFoundSolution)
            onFoundSolution(e->beg->index, e->end->index);
        
        solutions.push_back(pair<unsigned int, unsigned int>(e->beg->index, e->end->index));
    }
    
    e->beg->isRemoved = 0;
    e->end->isRemoved = 0;
}

void Graph::Mark(Vertex *v, int *markerVal)
{
    if (v->marker != nullptr)
    {
        *markerVal = *(v->marker);
        return;
    }
    
    if (v->isRemoved) return;
    
    v->marker = markerVal;
    
    for (auto it : v->adjacents)
        Mark(it, markerVal);
}

void Graph::CleanUp()
{
    for (auto it : vertices) delete it;
    for (auto it : edges) delete it;
    
    vertices.clear();
    edges.clear();
}

void Graph::onLoadedVertices(unsigned int n)
{
    CleanUp();
    
    for (int i = 0; i < n; ++i)
        vertices.push_back(new Vertex(i));
}

void Graph::onLoadedEdge(unsigned int b, unsigned int e)
{
    edges.push_back(new Edge(vertices[b], vertices[e]));
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
