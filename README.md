# Solution to Homework3 CS411 UAF
This solution has two parts:
* Finds the greatest contiguous sum 
* Finds the number of inversions in a sequence

This project was developed in Clion.
The solution consists of two files contigsum.hpp and inversions.hpp.
The test files are contigsum_test.cpp and inversions_test.cpp

# The Problem
As stated in HW3_instructions, there are two goals
* Find the greatest contiguous sum faster than O(nlogn) time 
** Define the template funciton contigSum(RAIter first, RAIter last)
* Find the number of inversions in a sequence faster than O(n^2) time
** Define the template function inversions(RAIter first, RAIter last)

These are accomplished by implementing divide-and-conquere algorithms

# Key Highlights
## Part A
The biggest thing that I had to tackle with was the idea of keeping track 
of multiple numbers and what the base case would be.

The base case is actually "base cases".
```c++
if(range == 0) {
        return Result{0,0,0,0};
    } else if (range == 1) {
        return Result{std::max(*first, 0), std::max(*first, 0), std::max(*first, 0), *first};
    }
```
Result is a struct that contains four variables: gcs, biggestSumWithFirst, biggestSumWithLast, 
and sumOfSequence. 
range is the size of the sequence if the sequence is size zero, then the biggest sum is 0, 
if the size is 1 then the biggest sum is either the element in that sequence or 0.

The case where the range is bigger than 1 is handled by this 
```c++
Result left = contigSumWorker(first, std::next(first, range/2));
            Result right = contigSumWorker(std::next(first, range/2), last);

            return Result{std::max(right.gcs,
                                   std::max(right.gcs,
                                            (left.biggestSumWithLast+right.biggestSumWithFirst))),
                          std::max(left.biggestSumWithFirst, (left.sumOfSequence+right.biggestSumWithFirst)),
                          std::max(right.biggestSumWithLast, (left.biggestSumWithLast+right.sumOfSequence)),
                          left.sumOfSequence+right.sumOfSequence};
```

## Part B
The key idea for finding the number of inversions it's the number elements jumped over when swapping, and not, 
how I thought at first, the number of times an element was swapped. In other words, the number of inversions 
is the distances that elements have to travel to make the sequence sorted.

The specification required that Merge Sort must be used, although modified to fulfill the objective.
This is done in one line.

```c++
 while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1) { // Must do comparison this way, to be stable.
            *out++ = *in2++;
            numInversions+= std::distance(in1, middle);
        }
        else
            *out++ = *in1++;
    }
```
The line that counts the distance traveled is where numInversions is incremented. numInversions is 
passed by reference to inversions, which then passes by reference to the mergesort function, and in turn passes it by
refernce to the stable merge function (which is where this code is in)

# License
[MIT](https://choosealicense.com/licenses/mit/)
