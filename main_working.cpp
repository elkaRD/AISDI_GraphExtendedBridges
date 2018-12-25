//
//  main.cpp
//  aisdi_grafy
//
//  Created by Robert on 24/12/2018.
//  Copyright © 2018 Robert. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

struct Edge;
struct Vertex;

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
    
    vector<Edge*> edges;
    vector<Vertex*> adjacents;
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

class Graph
{
public:
    void Load(string fileName)
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
                
                for (int i = 0;i < n; i++)
                    vertices.push_back(new Vertex(i));
                
                while (!file.eof())
                {
                    int b, e;
                    file >> b >> e;
                    if (b < 0 || b >= n || e < 0 || e >= n || b == e)
                    {
                        debug1 = b;
                        debug2 = e;
                        throw string("wrong input data: ");
                    }
                    edges.push_back(new Edge(vertices[b], vertices[e]));
                }
                
            }
            else throw "could not open the file " + fileName;
            file.close();
        }
        catch (string e)
        {
            cout << "Exception: " << e <<" "<<debug1<<" "<<debug2<< endl;
            //file.close()
        }
        catch (exception e)
        {
            cout << "Unknown exception: " << e.what() << endl;
        }
    }
    
    void Task()
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
    
    void StartMarking(Edge *e)
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
    
    void Mark(Vertex *v, int *markerVal)
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
    
    void CleanUp()
    {
        for (int i = 0; i < vertices.size(); i++) delete vertices[i];
        for (int i = 0; i < edges.size(); i++) delete edges[i];
        
        vertices.clear();
        edges.clear();
    }
    
private:
    vector<Vertex*> vertices;
    vector<Edge*> edges;
    
    int markerCounter;
};

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

int main(int argc, const char * argv[])
{
    //CreateFullGraph(200, "/Users/robert/studia/sem3/aisdi/aisdi_grafy/aisdi_grafy/data20.txt");
    
    Graph graph;
    graph.Load("/Users/robert/studia/sem3/aisdi/aisdi_grafy/aisdi_grafy/data3.txt");
    graph.Task();
    graph.CleanUp();
    
    cout<<"End of the program" << endl;
    
    return 0;
}
