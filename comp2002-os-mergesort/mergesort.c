/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
	int l = leftstart;
	int r = rightstart;
	int k = leftstart;

	while (l < leftend && r < rightend) {
		if (A[l] <= A[r])
			B[k++] = A[l++];
		else
			B[k++] = A[r++];
	}
	
	// Empty the remaining array into the temp B array
	while (l < leftend)
		B[k++] = A[l++];
	while (r < rightend)
		B[k++] = A[r++];

	// Copy the temp array from B back into A at the corresponding position
	memcpy(&A[leftstart], &B[leftstart], (rightend - leftstart + 1) * (sizeof(int)));
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
	if (left >= right)
		return; // One element remaining
	int mid = left + (right - left) / 2;

	// Split array down the middle
	my_mergesort(left,mid);
	my_mergesort(mid + 1, right);

	// Merge the two sorted halves back together
	merge(left, mid, mid + 1, right);
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
	// Allocate memory for one struct
	struct argument* arg = malloc(sizeof(struct argument)); // Implicity cast from the malloc returned void* to argument*

	// Handled failed malloc
	if (arg == NULL) {
		perror("Malloc failed when allocating space for the the args");
		exit(1);
	}

	arg->left = left;
	arg->right = right;
	arg->level = level;
	return arg;
}

