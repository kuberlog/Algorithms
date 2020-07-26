# Algorithms
![drone ci](https://drone.holons.ai/api/badges/kuberlog/algorithms/status.svg "CI")

This is a monorepo containing my workthrough of the Introduction to Algorithms book excercises and main algorithms.

## Caveats
- All algorithms and exercises are written in C. There is no psuedo-code here.
- The book uses notation `A[a .... d]` where a and d are both inclusive indicies. My code/notes uses `A[a:d]` notation where the min index is inclusive and the max index is exclusive.
- The makefile generates `.exe` file extensions because they are easier to track in `.gitignore`.

## How to run
```bash
# generate all the implemetation exe's
make
```

Sorting algorithms require data to be passed in via stdin. The `gensort.exe` program can be used to generate random data to sort. 

```bash
#                         data points (defaults to 100) 
#     max random val                                   |
#                   |                                  |
#  n data points    |                                  | 
#               |   |                                  |
./gensort.exe   50  100  |        ./insertion_sort.exe  50
```

# 2.1

## 2.1-1

### Question
Using Figure 2.2 as a model, illustrate the operation of INSERTION-SORT on the array A = {31, 41, 59, 26, 41, 58}

### Answer
```
{31, 41*, 59, 26, 41, 58}

{31, 41, 59*, 26, 41, 58}

{31, 41, 59, 26*, 41, 58}
 ||  ||  ||  ||
 | --^ --^ --^|
 ^------------

{26, 31, 41, 59, 41*, 58}
             ||  ||
	     | --^|
	     ^----

{26, 31, 41, 41, 59, 58*}
                 ||  ||
		 | --^|
		 ^----

{26, 31, 41, 41, 58, 59}
```

## 2.1-2

### Question
Rewrite the INSERTION-SORT procedure to sort into nonincreasing instead of non-decreasing order

### Answer
[insertion_sort_reverse.c](./insertion_sort_reverse.c)
```
7c7
<     for (j = i-1; j >= 0 && val < keys[j]; j--) {
---
>     for (j = i-1; j >= 0 && val > keys[j]; j--) {
```

## 2.1-3

### Question
Consider the searching problem:

__Input:__ A sequence of _n_ numbers _A = {a1, a2,...., an}_ and a value _v_

__Output:__ An index _i_ such that _v = A[i]_ or the special value `NIL` if _v_ does not appear in _A_

Write pseudocode for __linear search__, wich scans through the sequence, looking for _v_. Using a loop invariant, prove that your algorithm is correct. Make sure that your loop invariant fulfills the three necessary properties.


### Answer
I wrote real code.
[linear_search.c](./linear_search.c)

```C
int linear_search(int *A, int v, int len) {
  int i;
  for(i = 0; i < len; i++) {
    if(A[i] == v) {
      return i;
    }
  }
  return -1;
}
```

## 2.1-4

### Question
Consider the problem of adding two n-bit binary integers, stored in two n-element arrays A and B. The sum of the two integers should be stored in binary form in an (n+1)-element array C. State the problem formally and write pseudocode for adding the two integers.

### Answer

__Input:__ 2 _n_ bit arrays A = {a1, a2,...., an}, B = {b1, b2,....,bn}

__Output:__ An _n+1_ bit array C = {c1, c2,...., c(n+1)} that represents the sum of A & B


```C
void binary_addition(int *a, int *b, int *c, int len) {
        int i, sum, carry;
        carry = 0;
        for(i = len-1; i >= 0; i--) {
                sum = a[i] + b[i] + carry;
                c[i] = sum % 2;
                carry = sum / 2;
        }
}
```

# 2.2

## 2.2-1

### Question
Express the function `n^3/1000 - 100n^2 - 100n + 3` in terms of Θ-notation

### Answer
Θ(n^3)

## 2.2-2

### Question
Consider sorting n numbers stored in array A by first finding the smallest element of A and exchanging it with the element in A[1]. The find the second smallest element of A, and exchange it with A[2]. Continue in this manner for the first n-1 elements of A. Write (pseudo) code for this algorithim, wich is known as __selection sort__. What loop invariant does this algorithm maintain? Why does it need to run for only the first n-1 elements rather than for all n elements? Give the best-case and worst-case running times of selection sort in Θ-notation.

### Answer
```C
void selection_sort(int *keys, int len) {
  int i, j, min, tmp;
  for(i = 0; i < len-1; i++){
    min = i;

    // Find smallest
    for(j = i; j < len; j++) {
      if(keys[j] < keys[min]) {
        min = j;
      }
    }

    // Swap
    tmp = keys[i];
    keys[i] = keys[min];
    keys[min] = tmp;
  }
}
```

The loop invariant for the first loop is that keys[0:i] are sorted and are all less than any key in keys[i:len].

The loop invariant for the second loop is that min is the index of the smallest key in keys[i:j]. 

The second part of the first loop invariant ensures that all keys[0:len-1] are less than the last key and therefore all keys are sorted.

The best case and worst case are Θ(n^2). Even in the best case, the algorithm doesn't know that `i == min` ahead of time, so the second loop will still run an average of n/2-1 times.

## 2.2-3

### Question
Consider linear search again. How many elements of the input sequence need to be checked on the average, assuming that the element being searched for is equally likely to be any element in the array? How about in the worst case? What are the average-case and worst-case running times of linear search in Θ-notation? Justify your answers

### Answer

On average, n/2 items need to be checked in linear search. This is because each item has a 1/n chance of being the needle item. By the consideration of the n/2th item, there will be a 50% chance that the needle item will have already been found. The probability distribution is symetrical about the n/2 mark. Therefore, n/2 items will be checked on average.

Worst case senario, the item is not in the array and therefore n items will have to be considered to know that is the case. 

Θ(n) for both worst and average case because the `1/2` coefficient is dropped in Θ-notation

## 2.2-4

### Question

How can we modify almost any algorithm to have a good best-case running time?


### Answer

One can check to see if the problem is already solved.

## 2.3-1

### Question

Using Figure 2.4 as a model, illustrate the operation of merge sort on the array `A = {3, 41, 52, 26, 38, 57, 9, 49}`

### Answer

```
           {3,9,26,38,41,49,52,57}
                     ^
    {3,26,41,52}            {9,38,49,57}
         ^                       ^
 {3,41}     {26,52}     {38,57}     {9,49}
   ^           ^           ^          ^ 
{3}  {41}  {52}  {26}  {38}  {57}  {9}  {49}
```

## 2.3-2

### Question

Rewrite the `merge` procedure so that it does not use sentinels, instead stopping once either array `L` or `R` has had all its elements copied back to `A` and then copying the remainder of the other array back into `A`

### Answer
```C
void merge(int *A, int p, int q, int r) {
        int i, lInd, rInd;

        int lenLeft = q - p;
        int left[lenLeft];
        for(i = 0; i < lenLeft; i++) {
                left[i] = A[p + i];
        }

        int lenRight = r - q;
        int right[lenRight];
        for(i = 0; i < lenRight; i++) {
                right[i] = A[q + i];
        }

        lInd = 0;
        rInd = 0;

        for(i = 0; i < lenLeft + lenRight; i++) {
                if(lInd < lenLeft && (rInd >= lenRight || left[lInd] <= right[rInd])) {
                        A[p + i] = left[lInd];
                        lInd++;
                } else {
                        A[p + i] = right[rInd];
                        rInd++;
                }
        }
}
```

## 2.3-3

### Question

Use mathematical induction to show that when n is an exact power of 2, the solution of the recurrence

`T(n) = {2 if n=2, 2T(n/2)+n if n = 2^k, for k > 1}`

is `T(n) = nlgn`

### Answer
```
Basis: T(2) = 2 = 2lg2 = 2*1
Induction: assume recurrance T(2^k) = (2^k)lg(2^k)
	consider T(2^(k+1)):
	T(k+1) =	2T((2^(k+1))/2)+2^(k+1): substitution in original eq
	T(k+1) =	2T(2^k)+2^(k+1): fraction reduction
	T(k+1) =	2((2^k)lg(2^k))+2^(k+1): substitute induction assumption
	T(k+1) = 2^(k+1)lg(2^k)+2^(k+1): exponent rules
	T(k+1) = 2^(k+1)k+2^(k+1): log rules
	T(k+1) = 2^(k+1)*(k+1): exponent rules
	T(k+1) = 2^(k+1)*lg(2^(k+1)): log definition
	if n=2^(k+1) then T(n) n*lg(n)
	therefore recurrance holds for k+1 when it is assumed true for k
therefore the reccurance is proved true by induction
```

## 2.3-4

### Question

We can express insertion sort as a recursive procedure as follows. In order to sort `A[1...n]`, we recursively sort `A[1...n-1]` and then insert A[n] into the sorted array `A[1..n-1]`. Write a recurrence for the running time of this recursive version of insertion sort.

### Answer

`T(n) = {T(n-1)+n if n>1; n if n == 1}`

## 2.3-5

### Question

Referring back to the searching problem (see Excercise 2.1-3), observe that if the sequence A is sorted, we can check the midpoint of the sequence against v and eliminate half of the sequence from further consideration. The __binary search__ algorithm repeats this procedure, halfing the size of the remaining portion of the sequence each time. Write (pseudo) code , either iterative or recursive, for binary search. Argue that the worlst-case running time of binary search is Θ(nlgn)

### Answer

[binary_search.c](./binary_search.c)

```C
int binary_search(int *A, int needle, int lower, int upper) {
        // base
        if((upper - lower) <= 1) {
                if(A[lower] == needle) return lower;
                else return -1;
        }

        // recurse
        int pivot = (upper-lower)/2 + lower;
        if(needle < A[pivot]) return binary_search(A, needle, lower, pivot);
        else return binary_search(A, needle, pivot, upper);
}
```
