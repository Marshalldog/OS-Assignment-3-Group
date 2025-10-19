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
	while (i <= leftend){
		B[k]=A[i];
		k++;
		i++;
	}

	//copy any remaining element left in A[rightstart -> rightend] into B
	while (j <= rightend){
		B[k]=A[j];
		k++;
		j++;
	}

	//copy the result from B back into A using memcpy
	memcpy(&A[leftstart], &B[leftstart], (rightend - leftstart + 1)*(sizeof(int)));
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
	/* the arg funciton parameter passed in is a generic void* arg 
	thus the compliler doesnt know what type of data this void* arg is
	know that the caller passed in a point to a struct argument
	thus cast back to this ie:
	"treat this pointer as a pointer to a struct argument so i can safely use it"
	*/

	struct argument *a  = (struct argument *) arg;

	//access and save the data members
	int left = a->left;
	int right = a->right;
	int level = a->level;

	//base cases
		//base case 1: the range has zero or 1 elements so it is already sorted
		if (left >= right){
			// free argument struct as it was allocated with malloc
			free(a);
			return NULL;
		}

		// case case 2: reached or exeeded the cuttoff recusion depth so use normal merge sort
		if (level >= cutoff){
			my_mergesort(left,right); //call to normal merge sort
			free(a);
			return NULL;
		}

	// recursive case: create threads for parallel
		// calculate midpoint of the array
			int mid = left + ((right-left)/2);

		// create the new argument structs to pass to threads
		struct argument * al = buildArgs(left, mid, level+1);
		struct argument * ar = buildArgs(mid+1, right, level+1);

		// declare thread ID variables to store IDs of threads
		pthread_t tid1, tid2;

		//create the two threads
		// pass in the address of pointer ID 
		pthread_create(&tid1, NULL, parallel_mergesort, al);
		pthread_create(&tid2, NULL, parallel_mergesort, ar);

		//use pthreaad_join to wait until both sub arrays are sorted before continuing
		pthread_join(tid1,NULL);
		pthread_join(tid2,NULL);

		//once both halves are correctly sorted then can safely call merge on two subarrays
		merge(left,mid,mid+1,right);

		/* pointer a points to memory of a dynamically allocated struct argument from 
		build args function a level up in the recussion so must free it */
		free(a);

		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
		//allocate memory for the stuc using malloc
		//malloc returns void* but it is implicilty cast to struct argument* pointer
		struct argument* arg = malloc(sizeof(struct argument));

		//throw error in case malloc fails
		if (arg == NULL){
			perror("Build arg: malloc failed");
			exit(1);
		}

		//set the data members
		arg->left = left;
		arg->right = right;
		arg->level = level;

		//return
		return arg;
}