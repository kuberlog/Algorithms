#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define DEBUG 0

struct SubArray {
	int start;
	int end;
	int sum;
};

struct SubArray max_subarray_bruteforce(int* A, int start, int end) {
        int i, j, sum;
        struct SubArray rv;
        rv.sum = INT_MIN;
        for(i = start; i < end; i++) {
                sum = A[i];
                if(sum > rv.sum) {
                        rv.start = i;
                        rv.end = i+1;
                        rv.sum = sum;
                }
                for(j = i+1; j < end; j++) {
                        sum = sum + A[j];
                        if(sum > rv.sum) {
                                rv.start = i;
                                rv.end = j+1;
                                rv.sum = sum;
                        }
                }
        }

        return rv;
}

struct SubArray cross_max_subarray(int *A, int start, int mid, int end) {
	int right_max, left_max, right_sum, left_sum, sum, i;
	left_sum = right_sum = INT_MIN;
	left_max = mid;
	right_max = mid + 1;

	sum = 0;
	for(i = left_max; i >= start; i--) {
		sum = sum + A[i];
		if(sum > left_sum) {
			left_sum = sum;
			left_max = i;
		}
	}

	sum = 0;
	for(i = right_max; i < end; i++) {
		sum = sum + A[i];
		if(sum > right_sum) {
			right_sum = sum;
			right_max = i+1;
		} 
	}

	// remove sentinal value right loop never ran
	if(sum == 0) {
		right_sum = 0;
	}

	struct SubArray rv = {left_max, right_max, left_sum + right_sum};
	return rv;
}

struct SubArray max_subarray(int *A, int start, int end, int crossover) {
	int mid;
	struct SubArray left, right, cross;
	if(end-start <= crossover) {
		struct SubArray rv = max_subarray_bruteforce(A, start, end);
		return rv;
	}

	mid = (end+start)/2;
	left = max_subarray(A, start, mid, crossover);
	right = max_subarray(A, mid, end, crossover);
	cross = cross_max_subarray(A, start, mid, end);

	if(DEBUG) {
		printf("[%d:%d:%d]", start, mid, end);
		printf("left_sum: %d, cross_sum: %d, right_sum: %d\n", left.sum, cross.sum, right.sum);
	}
	if(left.sum >= right.sum && left.sum >= cross.sum) return left;
	if(right.sum >= left.sum && right.sum >= cross.sum) return right;
	return cross;
	
}

int main(int argc, char** argv) {
	int i, v, len;

	int CROSSOVER = 150;

	struct SubArray result;

	int* A = (int*) malloc(sizeof(int) * 10000000);

	len = 0;
	while(len < 10000000 && scanf("%d", &A[len]) != EOF) {
		len++;
	}

	result = max_subarray(A, 0, len, CROSSOVER);

	printf("\n\nresult: A[%d:%d] == %d\n", result.start, result.end, result.sum);

	free(A);
}


