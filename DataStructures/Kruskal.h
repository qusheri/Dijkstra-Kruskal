#pragma once
#include "DynamicArray.h"
#include "UndirectedGraph.h"
#include "../sorting_algorithms/QuickSort.h"
#include "HashTable.h"

template<typename Vertex, typename Weight>
class DSU {
private:
    HashTable<Vertex, Vertex> parent;
    HashTable<Vertex, int> rank;
public:
    DSU(DynamicArraySmart<Vertex> vertices) {
        for(int i = 0; i < vertices.GetLength(); i++) {
            parent.Add(vertices[i], vertices[i]);
            rank.Add(vertices[i], 0);
        }
    }
    Vertex Find(Vertex& x){
        if(parent.Get(x) == x) return x;
        parent.Get(x) = Find(parent.Get(x));
        return parent.Get(x);
    }
    void Union(Vertex x, Vertex y){
        x = Find(x);
        y = Find(y);
        if(x == y) return;
        if(rank.Get(x) < rank.Get(y)){
            parent.Get(x) = y;
        } else if(rank.Get(x) > rank.Get(y)){
            parent.Get(y) = x;
        } else {
            parent.Get(y) = x;
            ++rank.Get(x);
        }
    }
};

template <typename V, typename W>
int cmpEdge(Arc<V, W> a, Arc<V, W> b) {
    if(a.data->GetCost() < b.data->GetCost()) return -1;
    if(a.data->GetCost() > b.data->GetCost()) return 1;
    return 0;
}

template <typename Vertex, typename Weight>
DynamicArraySmart<Arc<Vertex, Weight>> KruskalMST(
    UndirectedGraph<Vertex, Weight>& graph,
    int vertexCount,
    ISorter<Arc<Vertex, Weight>>* sorter
)
{
    auto edges = graph.GetAllEdgesOnce();

    sorter->Sort(&edges, cmpEdge);

    DSU<Vertex, Weight> dsu(graph.GetAllVertices());

    DynamicArraySmart<Arc<Vertex, Weight>> mst;
    auto edgesIt = edges.GetIterator();
    while(!edgesIt->atEnd()){
        auto e = **edgesIt;
        int ru = dsu.Find(e.from);
        int rv = dsu.Find(e.to);
        if(ru != rv){
            dsu.Union(ru, rv);
            mst.Append(e);
        }
        ++(*edgesIt);
    }

    return mst;
}
