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

	while (l <= leftend && r <= rightend) {
		if (A[l] <= A[r])
			B[k++] = A[l++];
		else
			B[k++] = A[r++];
	}
	
	// Empty the remaining array into the temp B array
	while (l <= leftend)
		B[k++] = A[l++];
	while (r <= rightend)
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

// Type void * as pthread_create requires a function pointer
void * parallel_mergesort(void *arg){
	// Cast to a argument struct pointer so we can derefence our three variables.
	struct argument *a = (struct argument *) arg;
	int left = a->left, right = a->right, level = a->level;

	// Single elemet (sorted) or empty array
	if (left >= right) {
		return NULL; // Don't require a value to be returned;
	}

	// If the level has reach a maximum, use serial mergesort
	if (level >= cutoff) {
		my_mergesort(left,right);
		return NULL;
	}

	int mid = left + (right - left) / 2;
	pthread_t leftThread, rightThread; // Pointer to thread IDs

	// Create new thread to run parallel mergesort on the left half of the curr array.
	struct argument* leftArgs = buildArgs(left,mid,level+1);
	int thread_left_failed = pthread_create(&leftThread, NULL, parallel_mergesort, leftArgs);
	if (thread_left_failed) {
		perror("Left thread creation failed");
		exit(1);
	}

	// Create new thread to run parallel mergesort on the right half of the curr array.
	struct argument* rightArgs = buildArgs(mid+1,right,level+1);
	int thread_right_failed = pthread_create(&rightThread, NULL, parallel_mergesort, rightArgs);
	if (thread_right_failed) {
		perror("Right thread creation failed");
		exit(1);
	}

	// Wait for the threads to finish
	int join_left_failed = pthread_join(leftThread,NULL);
	int join_right_failed = pthread_join(rightThread,NULL);

	if (join_left_failed || join_right_failed) {
		perror("Thread joining failed");
		exit(1);
	}

	// Merge the two parallel sorted halves back together
	merge(left, mid, mid + 1, right);

	free(a); // free memory allocated in buildArgs
	return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
	// Allocate memory for one struct
	struct argument* arg = malloc(sizeof(struct argument)); // Implicity cast from the malloc returned void* to argument*

	// Handle failed malloc
	if (arg == NULL) {
		perror("Malloc failed when allocating space for the the args");
		exit(1);
	}

	// Assign the struct members the correct value to be passed through
	arg->left = left;
	arg->right = right;
	arg->level = level;
	return arg;
}

