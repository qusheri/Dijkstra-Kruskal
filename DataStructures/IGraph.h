#pragma once
#include "DynamicArray.h"
#include "ShrdPtr.h"
#include "IArc.h"

template <typename Vertex, typename Weight>
class IGraph {
public:
    virtual ~IGraph() = default;

    virtual void AddVertex(const Vertex& v) = 0;
    virtual void RemoveVertex(const Vertex& v) = 0;
    virtual bool HasVertex(const Vertex& v) const = 0;

    virtual void AddEdge(const Vertex& u, const Vertex& v, ShrdPtr<IArc<Weight>> data) = 0;
    virtual void RemoveEdge(const Vertex& u, const Vertex& v) = 0;
    virtual bool HasEdge(const Vertex& u, const Vertex& v) const = 0;

    virtual int GetVertexCount() const = 0;
    virtual int GetEdgeCount() const = 0;

    virtual DynamicArraySmart<Vertex> GetAllVertices() = 0;
};
