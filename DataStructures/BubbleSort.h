#pragma once

#include "ISorter.h"

template <typename T>
class BubbleSort : public ISorter<T> {
public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(T, T)) override {
        int n = seq->GetLength();
        for (int i = 0; i < n; i++) {
        auto it = seq->GetIterator();
            for (int j = 0; j < n - 1 - i; ++j) {
                if (cmp(**it, *(*it + 1)) > 0) {
                    T temp = **it;
                    **it = *(*it + 1);
                    *(*it + 1) = temp;
                }
                ++*it;
            }
        }
        return seq;
    }
};
