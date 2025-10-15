/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"


//make 
//make clean


/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
	//i tracks index of read from left half
	//j tracks index of read from right half
	//k tracks where to place the next smallest element
	
	int i = leftstart;
	int j =  rightstart;
	int k = leftstart;

	while(i < leftend && j < rightend){ //runs until both i and j indexes have reached end points
		//if right is bigger than left, add left to B array (cause left small)
		//if right is bigger than left, add right to B array (cause right small)
		if(A[i] <= A[j]){
			//copies A-left (i) into B and indexes i, k
			B[k++] = A[i++];
			//k++;
			//i++;
		}else{
			//copies A-right (j) into B and indexes i, k
			B[k++] = A[j++];
			//k++;
			//j++;
		}
	}
	//copy remaining of array (when one array is done)
	while(i < leftend){
		//copies A-left (i) into B and indexes i, k
		B[k++] = A[i++];
		//k++;
		//i++;
	}
	//copy remaining of array (when one array is done)
	while(j < rightend){
		//copies A-right (j) into B and indexes i, k
		B[k++] = A[j++];
		//k++;
		//j++;
	}

	//copy arrangement of B back into A
	//destination,location,size of transfer
	memcpy(&A[leftstart],&B[leftstart], (rightend - leftstart + 1) * sizeof(int));

}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
	//checks if sort is done
	if(left>=right){
		return;
	}
	//calculates the mid index of right and left
	int mid = left + ((right - left) >> 1);
	//sort left half
	my_mergesort(left, mid);
	//sort right half
	my_mergesort(mid+1, right);
	//mergesort left and right half
	merge(left, mid, mid+ 1, right);
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
	//struct argument *a_container 
	return NULL;
}

