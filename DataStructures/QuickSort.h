#pragma once

#include "ISorter.h"

template <typename T>
class QuickSort : public ISorter<T> {
private:
    int Partition(Sequence<T>* seq, int low, int high, int (*cmp)(T, T)) {
        auto itHigh = seq->GetIterator();
        *itHigh += high;
        T pivot = **itHigh;
        int i = low - 1;
        auto itI = seq->GetIterator();
        auto itJ = seq->GetIterator();
        if(low - 1 > 0) {
            *itI += low - 1;
        }
        if(low > 0) {
            *itJ += low;
        }
        for (int j = low; j < high; ++j) {
            if (cmp(**itJ, pivot) <= 0) {
                ++i;
                if(i > 0) {
                    ++* itI;
                }
                T temp = **itI;
                **itI = **itJ;
                **itJ = temp;
            }
            ++*itJ;

        }
        ++*itI;
        T temp = **itI;
        **itI = **itHigh;
        **itHigh = temp;
        return i + 1;
    }

    void QuickSortHelper(Sequence<T>* seq, int low, int high, int (*cmp)(T, T)) {
        if (low < high) {
            int pi = Partition(seq, low, high, cmp);
            QuickSortHelper(seq, low, pi - 1, cmp);
            QuickSortHelper(seq, pi + 1, high, cmp);
        }
    }

public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(T, T)) override {
        QuickSortHelper(seq, 0, seq->GetLength() - 1, cmp);
        return seq;
    }
};
