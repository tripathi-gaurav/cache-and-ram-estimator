### Cache statistics

`make check` to run the cache statistics

#### Working

The idea is to work on an array of size two and continue to increase it till size 2 ^ 24 (16 Mb).
For each array, the integer stored in the array is read and incremented. Accesses are performed on the first slot of the array and then incremented by `stride` positions.

As per the answer mentioned here: https://stackoverflow.com/questions/19136846/write-a-program-to-get-cpu-cache-sizes-and-levels/19142024#19142024

The CPU will prefetch can issue 2 prefetches per stream request, and so according to the post, we use `(i * 64) % (lengthMod - 1)`.
Whenever a cache miss is caused, there should be a steep increase in the time taken for the read write operation, which will help us identify the different cache levels.

---
### RAM estimator

`make ram` to run the memory calculator

#### Working

We have attempted to avoid using any system specific files/libraries. The logic relies on `malloc()` and `memset()` in order to allocate map memory and fill it up. Initially the program will keep asking for double memory from the system till it fails. Then the program looks at the difference between the successful allocation and failed allocation (double of successful allocation) and decides on an `incrementOrder` and requests for additional memory depending on that order till it fails. After failing, the program will again look at the difference between the successful allocation and failed allocation and derive a new `incrementOrder` and repeat the above steps till the the difference is negligible.
