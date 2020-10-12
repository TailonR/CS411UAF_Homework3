//
// Created by renew on 10/8/2020.
//

#ifndef HOMEWORK3_INVERSIONS_HPP
#define HOMEWORK3_INVERSIONS_HPP
#include <vector>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <type_traits>




// stableMerge
// Merge two halves of a sequence, each sorted, into a single sorted
// sequence in the same location. Merge is done in a stable manner.
// Requirements on Types:
//     FDIter is a forward iterator type.
//     The value type of FDIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, middle) and [middle, last) are valid ranges, each sorted
//      by <.
// Post:
//     [first, last) contains the same items as it did initially, but
//      now sorted by < (in a stable manner).
template <typename FDIter>
void stableMerge(FDIter first, FDIter middle, FDIter last, int &numInversions)
{
    // ** C++03:
    using Value = typename std::iterator_traits<FDIter>::value_type;
    // ** C++11:
//    using Value = typename remove_reference<decltype(*first)>::type;
    // ** Is this really better?

    std::vector<Value> buffer(distance(first, last));
    // Buffer for temporary copy of data
    FDIter in1 = first;         // Read location in 1st half
    FDIter in2 = middle;        // Read location in 2nd half
    auto out = buffer.begin();  // Write location in buffer
    // ** auto! That *is* better than std::vector<Value>::iterator

    // Merge two sorted lists into a single list in buff.
    while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1) { // Must do comparison this way, to be stable.
            *out++ = *in2++;
            numInversions+= std::distance(in1, middle);
        }
        else
            *out++ = *in1++;
    }

    // Copy remainder of original sequence to buffer.
    // Only one of the following two copy calls will do anything, since
    //  the other is given an empty source range.
    copy(in1, middle, out);
    copy(in2, last, out);

    // Copy buffer contents back to original sequence location.
    copy(buffer.begin(), buffer.end(), first);
}


// mergeSort
// Sorts a sequence, using Merge Sort.
// Recursive.
// Requirements on Types:
//     FDIter is a forward iterator type.
//     The value type of FDIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, last) is a valid range.
// Post:
//     [first, last) contains the same items as it did initially,
//      but now sorted by < (in a stable manner).
template <typename FDIter>
void mergeSort(FDIter first, FDIter last, int &numInversions)
{
    // Compute size of sequence
    size_t size = distance(first, last);

    // BASE CASE
    if (size <= 1)
        return;

    // RECURSIVE CASE
    FDIter middle = first;
    advance(middle, size/2);  // middle is iterator to middle of range

    // Recursively sort the two lists
    mergeSort(first, middle, numInversions);
    mergeSort(middle, last, numInversions);

    // And merge them
    stableMerge(first, middle, last, numInversions);
}

template<typename RAIter>
size_t inversions(RAIter first, RAIter last) {
    int numOfInversions = 0;
    mergeSort(first, last, numOfInversions);
    return numOfInversions;
};
#endif //HOMEWORK3_INVERSIONS_HPP
