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

* mergesort.h

Defines the 4 functions that are required to complete the parallel merge sort, as well as variables that control array length, temporary array storage and the maximum number of levels (cutoff).

* mergesort.c

Responsible for distrubuting the merge-sort process amongst the designated number of threads and sorting the input array.

* test-base-case.c

Tests the merge-sort algorithm implementation on a single thread (any cutoff input is ignored and treated as 0). Used to verify the base case of the recursive process.

* test-mergesort.c

Tests the parallel merge-sort program which utilises multiple threads which recurse down the base case (serial merge-sort).

* Makefile

Builds both the *test-mergesort* and *test-base-case* programs and provides cleaning functionality.

* .gitignore

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
   ./test-merge-sort <n> <cutoff> <rand seed>
   ```
5. Clean up objects and dependancies with
```
make clean
```

## Features and usage

Summarise the main features of your program. It is also appropriate to
instruct the user how to use your program.
### Assessing the Serial Merge-Sort Implementation

After making the program the user can test the serial merge-sort implementation. For example, consider this command signature indication 100,000,000 elements to be sorted with a cutoff of 0 and a random seed of 50:
```
./test-base-case 100000000 0 50 
```


## Testing

This section should detail how you tested your code. Simply stating "I ran
it a few times and it seems to work" is not sufficient. Your testing needs
to be detailed here.

## Known Bugs

N/A

## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your own?
What kinds of errors did you get? How did you fix them?

What parts of the project did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this project? How well
did the development and testing process go for you?

## Sources Used

If you used any sources outside of the textbook, you should list them here. 
If you looked something up on stackoverflow.com or you use help from AI, and 
fail to cite it in this section, it will be considered plagiarism and dealt 
with accordingly. So be safe CITE!

