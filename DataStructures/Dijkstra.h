#pragma once

#include <optional>

#include "UndirectedGraph.h"
#include "DynamicArray.h"
#include "HashTable.h"

template <typename Vertex, typename Weight>
HashTable<Vertex, Weight>* Dijkstra(
    UndirectedGraph<Vertex, Weight>& graph,
    Vertex start,
    Weight inf
)
{
    if (!graph.HasVertex(start)) throw std::invalid_argument("Start vertex not found");

    int n = graph.GetVertexCount();

    auto vertices = graph.GetAllVertices();
    HashTable<Vertex, Weight> verticesMap(n);

    for(int i = 0; i < n; ++i) {
        verticesMap.Add(vertices[i], i);
    }

    DynamicArraySmart<Weight> dist(n);
    DynamicArraySmart<bool> visited(n);

    for (int i = 0; i < n; i++){
        dist.Append(inf);
        visited.Append(false);
    }
    dist[verticesMap.Get(start)] = Weight();
    for(int step = 0; step < n; step++){
        std::optional<Vertex> u = std::nullopt;
        Weight best = inf;
        for(int i = 0; i < n; i++){
            Vertex v = vertices[i];
            if(!visited[verticesMap.Get(v)] && dist[verticesMap.Get(v)] < best){
                best = dist[verticesMap.Get(v)];
                u = v;
            }
        }
        if(!u.has_value()) break;

        visited[verticesMap.Get(u.value())] = true;

        auto adjList = graph.GetAdjList(u.value());
        auto it = adjList.GetIterator();
        while(!it->atEnd()){
            auto e = **it;
            Vertex v = e.to;
            Weight w = e.data->GetCost();
            if(!visited[verticesMap.Get(v)]) {
                if(dist[verticesMap.Get(u.value())] + w < dist[verticesMap.Get(v)]){
                    dist[verticesMap.Get(v)] = dist[verticesMap.Get(u.value())] + w;
                }
            }
            ++(*it);
        }
    }
    auto res = new HashTable<Vertex, Weight>();
    for(int i = 0; i < n; i++) {
        res->Add(vertices[i], dist[verticesMap.Get(vertices[i])]);
    }
    return res;
}
