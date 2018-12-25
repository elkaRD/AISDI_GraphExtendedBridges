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

void Graph::Task()
{
    cout<<"Debug info: "<<endl;
    cout<<" verts count: "<<vertices.size()<<endl;
    cout<<" edges count: "<<edges.size()<<endl;
    
    size_t edgesCount = edges.size();
    
    for (int i = 0; i < edgesCount; i++)
    {
        
        edges[i]->beg->isRemoved = 1;
        edges[i]->end->isRemoved = 1;
        
        
        
        StartMarking(edges[i]);
        
        edges[i]->beg->isRemoved = 0;
        edges[i]->end->isRemoved = 0;
        
        //            if (markerCounter != 0)
        //            {
        //                //TODO: mark this adge as one of the solutions
        //                cout<<"SOLUTION: "<<edges[i]->beg->index<<"  "<<edges[i]->end->index<<endl;
        //            }
        //
        //            if (markerCounter < 0) cout<<endl<<"WTF "<<markerCounter<<endl;
    }
}

void Graph::StartMarking(Edge *e)
{
    for (auto it : vertices)
        it->marker = nullptr;
    
    //markerCounter = e->beg->adjacents.size() + e->end->adjacents.size() - 2;
    map<Vertex*, int> elems;
    for (auto it : e->beg->adjacents)
    {
        if (it != e->end)
            elems[it] = 0;
    }
    for (auto it : e->end->adjacents)
    {
        if (it != e->beg)
            elems[it] = 0;
    }
    
    markerCounter = elems.size();
    
    //Mark(e->beg, markerVal);
    //Mark(e->end, markerVal);
    
    int i = 1;
    //        for (int j = 0; j < e->beg->adjacents.size(); j++, i++)
    //        {
    //            Mark(e->beg->adjacents[j], i);
    //        }
    //
    //        for (int j = 0; j < e->end->adjacents.size(); j++, i++)
    //        {
    //            Mark(e->end->adjacents[j], i);
    //        }
    
    int *markerVal[markerCounter];
    
    map<Vertex*, int>::iterator it = elems.begin();
    while (it != elems.end())
    {
        markerVal[i-1] = new int;
        *markerVal[i-1] = i;
        //cout<<"edge "<<e->beg->index<<" "<<e->end->index<<"    launching for " << it->first->index<<endl;
        Mark(it->first, markerVal[i-1]);
        ++i;
        ++it;
    }
    
    map<int, int> finalCount;
    for (int j = 0; j < markerCounter; j++)
    {
        //cout<<"TEST: "<<*markerVal[j]<<endl;
        finalCount[*markerVal[j]] = 0;
        delete markerVal[j];
    }
    //cout<<"TEST------"<<endl;
    
    if (finalCount.size() > 1)
    {
        cout<<"Solution: " << e->beg->index<<"  "<<e->end->index<<endl;
    }
    
    if (finalCount.size() == 0)
    {
        cout<<"WTF counter: "<<markerCounter<<endl;
    }
}

void Graph::Mark(Vertex *v, int *markerVal)
{
    //if (v->marker == markerVal || v->isRemoved == 1) return;
    
    //v->marker = markerVal;
    //++markerCounter;
    //        if (v->marker == 0)
    //        {
    //            v->marker = markerVal;
    //            ++markerCounter;
    //        }
    
    if (v->isRemoved) return;
    
    if (v->marker != nullptr)
    {
        //cout <<"marking "<<v->index<<" with the value " << *markerVal<<endl;
        *markerVal = *(v->marker);
        return;
    }
    
    //        if (v->marker == 0)
    //        {
    //            --markerCounter;
    //            //return;
    //        }
    
    v->marker = markerVal;
    //TODO: dont use int markers -> use pointers to these int's; if algorithm meets already found vertex then change value under pointer
    //      so it from two markers we would get one marker; after algorithm create a set (or map) to count number of all different values
    
    for (auto it : v->adjacents)
        Mark(it, markerVal);
}

void Graph::CleanUp()
{
    //for (int i = 0; i < vertices.size(); i++) delete vertices[i];
    //for (int i = 0; i < edges.size(); i++) delete edges[i];
    
    for (auto it : vertices) delete it;
    for (auto it : edges) delete it;
    
    vertices.clear();
    edges.clear();
}

void Graph::onLoadedVertices(int n)
{
    CleanUp();
    
    for (int i = 0; i < n; ++i)
        vertices.push_back(new Vertex(i));
}

void Graph::onLoadedEdge(int b, int e)
{
    edges.push_back(new Edge(vertices[b], vertices[e]));
}
