# InitializableArray
Constant-Time Array Initialization

[![Build Status](https://travis-ci.org/amallia/InitializableArray.svg?branch=master)](https://travis-ci.org/amallia/InitializableArray)

## Problem definition
Assume we have an array A[1, n] l-bit entries where only a small fraction of them will be written and then the array will be discarded, but we need to initialize all the cells of A. The effort to initialize A may then be too large compared to the little use we will make of it.

## Solution
Use a second array D[1, n] and a stack S[1, s] (whose size is initially s = 0 and will become s = m). The following invariant will be maintained:

`A[i] has been written <==> 1 <= D[i] <= s AND S[D[i]] = i` 


## Usage

```cpp
#include <stdio>

#include "InitializableArray.hpp"

int main(int argc, char const *argv[]) {
// Initialize
arr:
    InitializableArray<int> array(100 /* size */, 0 /* default value */);

    // Iterate with for-range
    for (auto &&i : array) {
        std::cout << i << std::endl; // It prints 0
    }

    array.set(10 /* position */, 1 /* value */);
    std::cout << array[10] << std::endl; // It prints 10

    array.clear(10); // Clear position 10
    std::cout << array[10] << std::endl; // It prints 0 again

    // Iterate with for loop
    for (size_t i = 0; i < array.size(); ++i) {
        array.set(i, i); // It sets the position as value
    }

    array.clear(); // Clear all array
    for (auto &&i : array) {
        std::cout << i << std::endl; // It prints 0 again
    }
    return 0;
}
```