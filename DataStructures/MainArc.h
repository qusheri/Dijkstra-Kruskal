#pragma once
#include "ShrdPtr.h"
#include "IArc.h"

template <typename Vertex, typename Weight>
class Arc {
public:
    Vertex from;
    Vertex to;

    ShrdPtr<IArc<Weight>> data;

    Arc(const Vertex& f, const Vertex& t, ShrdPtr<IArc<Weight>> d)
        : from(f), to(t), data(d) {}

    Arc() : from(), to(), data(nullptr) {}
};