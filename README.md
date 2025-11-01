README.template

# Assignment 3 | Concurrency

* Authors: 
  * Ethan Taljaard (a1885048)
  * Kelly SANTRY (a1884945)
  * Josiah SANTOS (a1886681)

* Group name: Assignment 3 Groups 109

## Overview

This program aims to improve the sorting speed of the merge-sort sorting algorithm. However, it does not focus on optimising time and space complexity, but instead increases computational speed through multi-threaded optimisation.

Single-threaded merge-sort, also known as, serial merge-sort, utilises only one thread on one CPU core to sort array of length *n*. When implementing parallel merge-sort, multiple threads become available to distribute the sorting workload. At the discretion of the OS multi-process scheduler, the numerous threads can be spread across multiple CPU cores to increase performance, with each core only required to sort an array of size *n/N*, where N is the number of threads running concurrently.

## Manifest

> mergesort.h

Defines the 4 functions that are required to complete the parallel merge sort, as well as variables that control array length, temporary array storage and the maximum number of levels (cutoff).

> mergesort.c

Responsible for distrubuting the merge-sort process amongst the designated number of threads and sorting the input array.

> test-base-case.c

Tests the merge-sort algorithm implementation on a single thread (any cutoff input is ignored and treated as 0). Used to verify the base case of the recursive process.

> test-mergesort.c

Tests the parallel merge-sort program which utilises multiple threads which recurse down the base case (serial merge-sort).

> Makefile

Builds both the *test-mergesort* and *test-base-case* programs and provides cleaning functionality.

> .gitignore

Prevents object and dependency files from being committed to GitHub.


## Building the project

This section should tell the user how to build your code.  If you are
delivering a library, where does it need to be installed, or how do you use
it? Is this an executable, if so, how can a user get up to speed as fast as
possible?

1. Clone the project from GitHub, using 
```
git clone
```
2. Navigate to the directory: 
```
cd OS-Assignment-3-Group/comp2002-os-mergesort
```
3. Build the object files and dependancies for both testing files using 
```
make
```
4. Run the program using the following signatures:
  * To test the serial merge-sort functionality (1 thread) use:
    * *n* represents the size of the array to be sorted.
    * *cutoff* value will be 0 regardless of integer inputted (single thread)
    * *rand seed* is the

   ```
   ./test-base-case <n> <cutoff> <rand seed>
   ```

  * To test the parallel merge-sort functionality use:
    * *n* represents the size of the array to be sorted.
    * *cutoff* represents the number of times the input array is divided in half to be split between double the number of threads. i.e. a *cutoff* = 3 will result in 2<sup>3</sup> = 8 threads.
    * *rand seed* is the

   ```
   ./test-mergesort <n> <cutoff> <rand seed>
   ```
5. Clean up objects and dependancies with
```
make clean
```

## Features and usage

Summarise the main features of your program. It is also appropriate to
instruct the user how to use your program.
### Serial Merge-Sort Feature

After making the program the user can test the serial merge-sort implementation. For example, consider this command signature indication 100,000,000 elements to be sorted with a cutoff of 0 and a random seed of 50:
```
./test-base-case 100000000 0 50 
```
This provides the output:

![Demo base case not cuttoff](/comp2002-os-mergesort/images/test-base-case-cutoff-0-DEMO.png)

Importantly, adding a cutoff greater than 0 does not introduce multi-threading:
```
./test-base-case 100000000 5 50 
```

![Demo base case 5 cuttoff](/comp2002-os-mergesort/images/test-base-case-cutoff-5-DEMO.png)

Note that the small time differential here is likely a result of minor changes in single CPU resources available at the time of enter the command to run the test. Running the same command promt 5 times gives varied sort times:

![Demo base case 5 cuttoff](/comp2002-os-mergesort/images/5-base-case-demo.png)

### Parallel Merge-Sort Feature

To capture the power of multithreading, use *test-mergesort*. For example, consider this command signature indication 100,000,000 elements to be sorted with a variety of cuttoff levels and a random seed of 50:

![Demo base case 5 cuttoff](/comp2002-os-mergesort/images/running-para-many.png)

Increasing the number of cutoff levels, and hence, increasing the number of threads working to sort the array, reduces the time to taken to sort. In this snapshot, the number of threads increases as follow:
| Cutoff       | 1    | 2    | 3    | 4    | 5    | 6    |
| ------------ | ---- | ---- | ---- | ---- | ---- | ---- |
| Num Threads  | 2    | 4    | 8    | 16   | 32   | 64   |
| Sort Time (s)| 6.08 | 3.54 | 1.99 | 1.50 | 1.48 | 1.50 |

Interestingly, as the number of threads reaches 16 and then into 32 and 64, there is no increase in sorting time. This is a likely result of hardware limitations on the testing device (i.e. the number of cores is less than the numbre of desired threads) and/or the cost of creating and merging thread. See more in the [Testing Section](#testing).

## Testing
As previously stated, the primary objective of this program is to create a multi-thread optimized merge sort algorithm. Thereby, both the merge sort and the multi-threaded optimization should be tested independently to ensure that the merge sort is functional and that the multi-thread application improves the functionality. The mergesort.c code is structured so that the parallel_mergesort designates the threads to run subsections of the input array through the merge sort algorithm. This design allows for the merge sort algorithm to function independently from parallel_mergesort, making it the ideal starting point for testing.
> test-base-case.c

The purpose of this test case is to verify that the merge sort algorithm, without the multithreading functions as intended. This program will run on a single thread and will recursively call merge sort algorithm until completion. This test case generates a random array of numbers, using a seed and array size. The test case then starts a clock and passes the array to the merge sort function. The merge sort algorithm finishes and the change time is measured. Then the test case runs a scan through the output array to validate the sort. If the sorting validation is successful, the test case outputs the time performance metric. Otherwise, the test case throws an error. 

> test-mergesort.c

This test case functions almost identically to the test-base-case.c with one key difference being when the merge sort performs a recursive calls, it spits the workload between 2 thread, and will continue to do until it reaches the maximum number of threads (which were given in the program call). With the only difference between the cases being the addition of parallelized computation, the results of test operating with the same input will highlight the performance characteristics of these approaches.

> Testing Comparison

Test 1: Sample Size: 1000, Thread Count: 12, Seed: 12345
![Test Case 1](/comp2002-os-mergesort/images/N1000T12S12345.png)
A relatively small sample size of 1000 was used, and the resulting sorting times for completing were small. The multi-threaded test case complete within a sub-millisecond while the base case completed with a sub-second period. With such a small sample size, the performance difference between the test case are not highlighted well.

Test 2: Sample Size: 1000000, Thread Count: 12, Seed: 12345
![Test Case 2](/comp2002-os-mergesort/images/N1000000T12S12345.png)
With a larger input size, the performance of the multi-threaded program is 4 times greater than the non-multi-threaded. The parallelization of the task allowed for the task to be rapidly divided into small work loads, effectively maximising the usage of computer resources.

Test 3: Sample Size: 100000000, Thread Count: 12, Seed: 12345
![Test Case 3](/comp2002-os-mergesort/images/N100000000T12S12345.png)
The size of the input array is approaching the maximum integer this program can intake and operate on due to integer overflow. Due to the large test size, the parallelizated test case performs at a significant advantage due to the extended usage of a more computer resources. For this sample size, the non parallelizated merge sort performs almost 10 times worse due to poor resource usage.


## Known Bugs

when a sufficiently large input size is selected, an integer overflow occurs, causing the program to register a smaller input size.

## Reflection and Self Assessment

### Bugs
- One issue was a misunderstanding of the 'base case' parameters in

    ```
    merge(int leftstart, int leftend, int rightstart, int rightend)
    ```
    Which has ranges: left subarray [leftstart,leftend] and right subarray [rightstart,rightend].

    However, in our group's previous implementations of merge sort, arrays were merged with
    ```
    merge(int left, int mid, int right)
    ```
    where *mid* followed the last element of the left subarray and marked the first element of the right subarray (left subarray [left,mid) and right subarray [mid,right)).
    
    This confused our group for a while, but we rectified this after a lengthy discussion. 

### Challenges
- Before running the program in parallel, our group wanted to test our serial merge-sort functionality so we would have the 'base case' for parallel merge-sort verified. Here we struggled to adapt the provided testing script, but eventually figured out how to omit any cutoff and called *my_mergesort* directly.
- Understanding the thread creation API was a lengthy process once our group was ready to implement the parallel merge-sort. To learn more about the API, we not only consulted the textbook, but used multiple online sources (see [Sources](#sources-used)).

### Light Bulb Moments

- Learning how the void pointer used was valuable. It was interesting to learn how a void pointer allows for a universal interface that can be molded by the programmer. In the following example, arg (void *) type is explicity cast to an argument pointer so we can get the three members from the struct. This allows any number and type of arguments to be passed to the new thread.
```
struct argument *a = (struct argument *) arg;
int left = a->left, right = a->right, level = a->level;
```

## Sources Used

### ChatGPT
Gaining a further understanding of the thread and memory APIs:
```
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
```
- Why is the return type int?
- Why is does it require a function pointer and not just a function?
- Why does the start routine return a void pointer?
- What does this return?

```
int pthread_join(pthread_t thread, void **retval);
```
- What does this return?
```
void *memcpy(void *dest, const void *src, size_t n);
```
- What is the size? Size of a single element? Size of the whole array?

### YouTube

Understanding the merge-sort algorithm

[![Merge-Sort Vid Coding with John](https://i.ytimg.com/an_webp/bOk35XmHPKs/mqdefault_6s.webp?du=3000&sqp=CJW7-8cG&rs=AOn4CLD-PIQLrJQ_LG_YvBlT6goQKlirYg)](https://www.youtube.com/watch?v=bOk35XmHPKs)

[![Merge-Sort Vid Michael Sambol](https://i.ytimg.com/vi/4VqmGXwpLqc/hqdefault.jpg?sqp=-oaymwEnCNACELwBSFryq4qpAxkIARUAAIhCGAHYAQHiAQoIGBACGAY4AUAB&rs=AOn4CLDW2YYkkzIxpVrcfNZypIsT2AhoIw)](https://www.youtube.com/watch?v=4VqmGXwpLqc)

### Geeks for Geeks

Learning more about the thread and memory APIs:

* [Threads in C](https://www.geeksforgeeks.org/c/thread-functions-in-c-c/)
* [Memcpy](https://www.geeksforgeeks.org/cpp/memcpy-in-cc/)