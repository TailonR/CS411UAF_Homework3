// contigsum.hpp
// Tailon Russell
// Date: 10/8/2020.
// The header file for the template functions contigSum and contigSum worker
// as well as the struct Result

#ifndef HOMEWORK3_CONTIGSUM_HPP
#define HOMEWORK3_CONTIGSUM_HPP
#include <vector>
#include <deque>
#include <iostream>
struct Result {
    int gcs, biggestSumWithFirst, biggestSumWithLast, sumOfSequence;
};

// contigSumWorker
// returns the greatest contiguous sum,
//      the biggest sum that includes the first element,
//      the biggest sum that includes the last element,
//      and the sum of the entire sequence
// Requirements on types:
//      RAIter is a random access iterator type
// Pre:
//      [first, last) must be a valid range
template<typename RAIter>
Result contigSumWorker(RAIter first, RAIter last) {
    Result ListABCD;
    int range = std::distance(first, last);
    if(range == 0) {
        return Result{0,0,0,0};
    } else if (range == 1) {
        return Result{std::max(*first, 0), std::max(*first, 0), std::max(*first, 0), *first};
    }else {
            Result left = contigSumWorker(first, std::next(first, range/2));
            Result right = contigSumWorker(std::next(first, range/2), last);

            return Result{std::max(right.gcs,
                                   std::max(right.gcs,
                                            (left.biggestSumWithLast+right.biggestSumWithFirst))),
                          std::max(left.biggestSumWithFirst, (left.sumOfSequence+right.biggestSumWithFirst)),
                          std::max(right.biggestSumWithLast, (left.biggestSumWithLast+right.sumOfSequence)),
                          left.sumOfSequence+right.sumOfSequence};
    }
};

// contigSum
// returns the greatest contiguous sum of the sequence
// Requirements on types:
//      RAIter is a random access iterator type
// Pre:
//  [first, last) must be a valid iterator type
template<typename RAIter>
int contigSum(RAIter first, RAIter last) {
    return contigSumWorker(first, last).gcs;
};


#endif //HOMEWORK3_CONTIGSUM_HPP
