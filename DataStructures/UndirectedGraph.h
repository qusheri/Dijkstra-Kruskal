#pragma once

#include "IGraph.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "MainArc.h"

template <typename Vertex, typename Weight>
class UndirectedGraph : public IGraph<Vertex, Weight> {
private:
    typedef Arc<Vertex, Weight> ArcType;
    typedef LinkedListSmart<ArcType> ArcListType;
    HashTable<Vertex, ArcListType> adjacency;
    int edgeCount;

    bool cmp(const Vertex& a, const Vertex& b) const {
        return a < b;
    }

public:
    explicit UndirectedGraph(size_t cap = 16)
        : adjacency(cap),
          edgeCount(0)
    {}

    ~UndirectedGraph() override = default;

    void AddVertex(const Vertex& vid) override {
        if (!adjacency.ContainsKey(vid)) {
            LinkedListSmart< Arc<Vertex, Weight> > emptyList;
            adjacency.Add(vid, emptyList);
        }
    }
    void RemoveVertex(const Vertex& v) override {
        if (!adjacency.ContainsKey(v)) return;
        DynamicArraySmart<Vertex> vertices;
        auto& listV = adjacency.Get(v);
        auto itV = listV.GetIterator();
        int countLocal=0;
        while(!itV->atEnd()){
            countLocal++;
            ++(*itV);
        }
        edgeCount -= countLocal;

        auto tableIt = adjacency.GetIterator();
        while(!tableIt->atEnd()){
            int otherV = tableIt->GetCurrentKey();
            if(otherV != v){
                auto& list = adjacency.Get(otherV);
                auto it = list.GetIterator();
                int idx=0;
                while(!it->atEnd()){
                    auto e = **it;
                    if(e.to == v){
                        list.RemoveAt(idx);
                        edgeCount--;
                        break;
                    }
                    ++(*it);
                    idx++;
                }
            }
            ++(*tableIt);
        }

        adjacency.Remove(v);
    }

    void AddEdge(const Vertex& u, const Vertex& v, ShrdPtr<IArc<Weight>> data) override {
        if(!HasVertex(u)) {
            AddVertex(u);
        }
        if(!HasVertex(v)) {
            AddVertex(v);
        }
        if(cmp(u,v)) {
            Arc<Vertex, Weight> arc(u,v,data);
            adjacency.Get(u).Append(arc);
        } else {
            Arc<Vertex, Weight> arc(v,u,data);
            adjacency.Get(v).Append(arc);
        }
        ++edgeCount;
    }
    void RemoveEdge(const Vertex& u, const Vertex& v) override {
        if(!HasVertex(u) || !HasVertex(v)) return;
        if (cmp(u, v)) {
            auto& list = adjacency.Get(u);
            auto it = list.GetIterator();
            int idx=0;
            while(!it->atEnd()){
                auto e = **it;
                if(e.to == v){
                    list.RemoveAt(idx);
                    break;
                }
                ++(*it);
                idx++;
            }
            edgeCount--;
        }
        else {
            auto& list = adjacency.Get(v);
            auto it = list.GetIterator();
            int idx=0;
            while(!it->atEnd()){
                auto e = **it;
                if(e.to == u){
                    list.RemoveAt(idx);
                    break;
                }
                ++(*it);
                idx++;
            }
            edgeCount--;
        }
    }

    bool HasVertex(const Vertex& vid) const override {
        return adjacency.ContainsKey(vid);
    }

    bool HasEdge(const Vertex& u, const Vertex& v) const override {
        if (!HasVertex(u) || !HasVertex(v)) return false;
        if(cmp(v, u)) {
            auto& list = adjacency.Get(v);
            auto it = list.GetIterator();
            while(!it->atEnd()){
                auto e = **it;
                if(e.to == u) {
                    return true;
                }
                ++(*it);
            }
            return false;
        }
        else {
            auto& list = adjacency.Get(u);
            auto it = list.GetIterator();
            while(!it->atEnd()){
                auto e = **it;
                if(e.to == v) {
                    return true;
                }
                ++(*it);
            }
            return false;
        }
    }

    int GetVertexCount() const override {
        return adjacency.GetCount();
    }

    int GetEdgeCount() const override {
        return edgeCount;
    }

    DynamicArraySmart<Vertex> GetAllVertices() override {
        DynamicArraySmart<Vertex> res;
        auto tIt = adjacency.GetIterator();
        while(!tIt->atEnd()){
            Vertex key = tIt->GetCurrentKey();
            res.Append(key);
            ++(*tIt);
        }
        return res;
    }

    DynamicArraySmart<Arc<Vertex, Weight>> GetAdjList(const Vertex& x) {
        DynamicArraySmart<Arc<Vertex, Weight>> result;
        if(!HasVertex(x)) return result;

        auto& listX = adjacency.Get(x);
        auto itx = listX.GetIterator();
        while(!itx->atEnd()){
            result.Append(**itx);
            ++(*itx);
        }

        auto tIt = adjacency.GetIterator();
        while(!tIt->atEnd()){
            Vertex z = tIt->GetCurrentKey();
            if(cmp(z,x)){
                auto& listZ = adjacency.Get(z);
                auto iz = listZ.GetIterator();
                while(!iz->atEnd()){
                    auto& arc = **iz;
                    if(arc.to==x){
                        result.Append(arc);
                    }
                    ++(*iz);
                }
            }
            ++(*tIt);
        }
        return result;
    }

    DynamicArraySmart<Arc<Vertex, Weight>> GetAllEdgesOnce() {
        DynamicArraySmart<Arc<Vertex, Weight>> edges(edgeCount);
        auto tableIter = adjacency.GetIterator();
        while(!tableIter->atEnd()) {
            Vertex u = tableIter->GetCurrentKey();
            auto & listU = **tableIter;
            auto itList = listU.GetIterator();
            while(!itList->atEnd()) {
                auto e = **itList;
                if(cmp(u, e.to)) {
                    edges.Append(e);
                }
                ++(*itList);
            }
            ++(*tableIter);
        }
        return edges;
    }
};
