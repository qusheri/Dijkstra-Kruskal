#pragma once

#include "ISorter.h"

template <typename T>
class MergeSort : public ISorter<T> {
private:
    void Merge(Sequence<T>* seq, int left, int mid, int right, int (*cmp)(T, T)) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Sequence<T>* leftSeq = seq->GetSubsequence(left, mid);
        Sequence<T>* rightSeq = seq->GetSubsequence(mid + 1, right);

        auto leftIt = leftSeq->GetIterator();
        auto rightIt = rightSeq->GetIterator();
        auto seqIt = seq->GetIterator();
        (*seqIt) += left;

        int i = 0, j = 0, k = left; // leftIt - i, j - right, seqIt - k
        while (i < n1 && j < n2) {
            if (cmp(**leftIt, **rightIt) <= 0) {
                **seqIt = **leftIt;
                ++*leftIt;
                ++*seqIt;
                ++i;
                ++k;
            } else {
                **seqIt = **rightIt;
                ++*rightIt;
                ++*seqIt;
                ++k;
                ++j;
            }
        }

        while (i < n1) {
            **seqIt = **leftIt;
            ++*leftIt;
            ++*seqIt;
            ++i;
            ++k;
        }

        while (j < n2) {
            **seqIt = **rightIt;
            ++j;
            ++k;
        }
    }

    void MergeSortHelper(Sequence<T>* seq, int left, int right, int (*cmp)(T, T)) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            MergeSortHelper(seq, left, mid, cmp);
            MergeSortHelper(seq, mid + 1, right, cmp);
            Merge(seq, left, mid, right, cmp);
        }
    }

public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(T, T)) override {
        MergeSortHelper(seq, 0, seq->GetLength() - 1, cmp);
        return seq;
    }
};
