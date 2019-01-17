//
//  Graph.cpp
//  aisdi_grafy
//
//  Created by Robert on 25/12/2018.
//  Copyright © 2018 Robert. All rights reserved.
//

#include "Graph.hpp"

using namespace std;

/*void GraphLoader::Load(const string fileName)
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
}*/

void GraphLoader::Load(std::istream &input)
{
    int debug1;
    int debug2;
    
    try
    {
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
                    debug1 = b;
                    debug2 = e;
                    throw std::string("wrong input data: ");
                }
                onLoadedEdge(b, e);
                cout<<"Added edgee: "<<b<<" "<<e<<endl;
                //TODO: fix problem with loading ethe last line
            }
            
        }
        //else throw "could not open the file " + fileName;
        //file.close();
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

void GraphLoader::CreateK(const unsigned int k)
{
    onLoadedVertices(k);
    
    for (unsigned int i = 0; i < k-1; ++i)
        for (unsigned int j = i+1; j < k; ++j)
            onLoadedEdge(i, j);
}

vector<pair<unsigned int, unsigned int> > Graph::Task()
{
    solutions.clear();
    
    for (const auto &it : edges)
        StartMarking(it);
    
    return solutions;
}

void Graph::StartMarking(Edge *e)
{
    for (auto &it : vertices)
        it->isRemoved = 0;
    
    e->beg->isRemoved = 1;
    e->end->isRemoved = 1;
    
    unordered_set<Vertex*> elems;
    for (const auto &it : e->beg->adjacents)
    {
        if (it != e->end)
            elems.insert(it);
    }
    for (const auto &it : e->end->adjacents)
    {
        if (it != e->beg)
            elems.insert(it);
    }
    
    counter = 0;
    Mark(*(elems.begin()));
    
    if (counter != vertices.size() - 2)
    {
        if (onFoundSolution)
            onFoundSolution(e->beg->index, e->end->index);

        solutions.push_back(pair<unsigned int, unsigned int>(e->beg->index, e->end->index));
    }
}

void Graph::Mark(Vertex *v)
{
    v->isRemoved = 1;
    ++counter;
    
    for (const auto &it : v->adjacents)
        if (!it->isRemoved)
            Mark(it);
}

Graph::~Graph()
{
    CleanUp();
}

void Graph::CleanUp()
{
    for (auto &it : vertices) delete it;
    for (auto &it : edges) delete it;
    
    vertices.clear();
    edges.clear();
}

void Graph::onLoadedVertices(unsigned int n)
{
    CleanUp();
    
    vertices.reserve(n);
    
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

std::istream& operator >> (std::istream &in, Graph &right)
{
    right.Load(in);
    return in;
}
