#pragma once

#include "../DataStructures/Sequence.h"

template <typename T>
class ISorter {
public:
    virtual Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(T, T)) = 0;
    virtual ~ISorter() {}
};