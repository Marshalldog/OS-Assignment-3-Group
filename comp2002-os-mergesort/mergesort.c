/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
	//initalise the indexes:
	int i = leftstart; // i is the start of L[] array which is A[leftstart->leftend]
	int j = rightstart; // j is the start of R[] array which is A[righttstart->rightend]
	int k = leftstart; // k is start index of temp memory used in B

	//merge the results into memory in B
	while (i <= leftend && j <= rightend){
		// check which value is lower in the two array halves
		if (A[i] <= A[j]){
			//put lower value into correct slot of B
			B[k] = A[i];
			i++; //L[i] was lower so increment i
		} else { // A[i] > A[j]
			//put lower value into correct slot of B
			B[k] = A[j]; 
			j++; //R[j] was lower so increment j
		}
		k++; //increment k so at correct part of B
	}

	//copy any remaining element left in A[leftstart -> leftend] into B
	while (i < leftend){
		B[k]=A[i];
		k++;
		i++;
	}

	//copy any remaining element left in A[rightstart -> rightend] into B
	while (j < rightend){
		B[k]=A[j];
		k++;
		j++;
	}

	//copy the result from B back into A using memcpy
	memcpy(&A[leftstart], &B[rightstart], (rightend - leftstart + 1)*(sizeof(int)));

}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
	//left is left index, right is the right-most index in array A[l] -> A[r]
	if (left < right){
		//calculate mid point
		int m = left + (right-left)/2;

		//sort the two halves, do recursive call
		my_mergesort(left,m);
		my_mergesort(m+1,right);

		//merge two sorted arrays
		merge(left,m,m+1,right);
	}
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
		return NULL;
}

