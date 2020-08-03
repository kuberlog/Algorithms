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

## 2.3-6

### Question

Observe that the while loop of lines 5-7 of the insertion_sort procudure in Section 2.1 uses a linear search to scan (backward) through the sorted subarray A[1..j-1]. Can we use a binary search instead to improve the worst-case running time of insertion sort to Θ(nlgn)?

### Answer

No. Insertion sort also shifts the elements to the right when scanning the array to find the insertion point. The element shifting would still need to happen and that process is Θ(n) regardless of how the insertion point is found.

## 2.3-7

### Question

Describe a Θ(nlgn)-time algorithm that, given a set `S` of `n` integers and another interger `x`, determines whether or not there exist two elements in `S` whose sum is exactly `x`.


### Answer

[sum_in_set.c](./sum_in_set.c)
```C
void sum_in_set(int *S, int sum, int len, int *rv) {
        int i, needle;
        merge_sort(S, 0, len); // O(nlgn)
        for(i = 0; i < len; i++) { // O(n) (loop without contents)
                rv[0] = i;
                needle = sum - S[i];
                rv[1] = binary_search(S, needle, 0, len); // O(lgn)
                if(rv[1] > -1) return;
        } // O(nln) (loop with contents)
        rv[0] = -1;
        rv[1] = -1;
				
				// O(nlgn) + O(nlgn) = O(nlgn)
}
```

# Ch 2 Problems

## 2-1

### Question

Although merge sort runs in Θ(nlgn) worst-case time and insertion sort runs in Θ(n^2) worst-case time, the constant factors in insertion sort can make it faster in practice for small problem sizes on many machines. Thus, it makes sense to coarsen the leaves of the recursion by using insertion sort within merge sort when subproblems become sufficiently small. Consider a modification to merge sort in which `n/k` sublists of length `k` are sorted using insertion sort and then merged using the standard merging mechanism, where `k` is a value to be termined

__a.__ Show that insertion sort can sort the n/k sublists, each of length k, in `Θ(nk)` worst-case time.

__b.__ Show how to merge the sublists in `Θ(nlg(n/k))` worst case time

__c.__ Given that the modified algorithm runs in `Θ(nk + nlg(n/k))` worst-case time, what is the largest value of k as a function of n for which the modified algorithm has the same running time as standard merge sort, in terms of Θ-notation?

__d.__ How should we choose `k` in practice?


### Answers

__a.__ 
Insertion sort on k items runs in Θ(k^2). If insertion_sort is called n/k times, then that is Θ(n/k) * Θ(k^2) = Θ(nk)

__b.__
It takes Θ(n) to a single level of merge (across all subliests, every item has to be merged into another sublist (and eventually the top level list)). To achieve n/k sublists by recursively dividing collections in half, it takes lg(n/k) levels of recursion. Therfore, to merge all recursions it takes Θ(nlg(n/k)) time.

__c.__ 
For large enough k's the term `nk` will dominate in Θ(nk + nlg(n/k)). As long as `k(n)` is Θ(lg(n)), then k will be small enough to rival pure mergesort.


__d.__
Make k some constant and titrate `k` using real machine timings for expected input size n. The appropriate value will be bounded by context of expected size n and real hardware.

## 2-2

### Question

Bubblesort is a popular, but inefficient, sorting algorithm. It works by repeatedly swapping adjacent elements that are out of order.

```
BUBBLESORT(A)
1  for i = 1 to A.length - 1
2    for j = A.length downto i + 1
3      if A[j] < A[j - 1]
4        exchange A[j] with A[j - 1]
```
 __a.__ Let `A'` denote the output of `BUBBLESORT(A)`. To prove that `BUBBLESORT` is correct, we need to prove that it terminates and that `A'[1] <= A'[2] <= ... <= A'[n]`,

 where `n = A.length`. In order to show that `BUBBLESORT` actually sorts, what else do we need to prove?

 The next two parts will prove inequality (2.3).

 __b.__ State precisely a loop invariant for the `for` loop in lines 2-4, and prove that this loop invariant holds. Your proof should use the structure of the loop invariant proof presented in this chapter.

 __c.__ Using the termination condition of the loop invariant proved in part (b), state a loopi nvariant for the `for` loop in lines 1-4 that will allow you to prove inequality (2.3). Your proof should use the structure of the loop invariant proof presented in this chapter.

 __d.__ What is the worst-case running time of bubblesort? How does it compare to the running time of insertion sort?


 ### Answer

 __a.__ We need to prove that A' contains the same elements as A

 __b.__ On each iteration A[j] will be the smallest item of A[j ... A.length].  

 Initialization: At the start of the loop, j is A.length, so A[j ... A.length] is of length 1 and therefore A[j] is the smallest item

 Maintanance: If A[j] is smaller of A[j-1] then the two are echanged, meaning the smallest number is propagated to the left and that number will be A[j] on the next loop

 Termination: When the loop terminates j-1 will be equal to i and so A[i] will be the smallest number of A[i ... A.length]

 __c.__ On each iteration A[1 ... i] will be sorted

 Initialization: At the start of the loop, i = 1 meaning that A[1 ... i] is of length 1 and therefore is sorted

 Maintanance: At the end of each loop j-1 will be equal to i. Since the termination quality of the inner loop is that A[i] will be the smallest number of A[i .. A.length] it will be the case that no number in A[i+1 ... A.length] should come before A[i] in the sorted list A' and therefore the invariant holds.

 Termination: When the loop terminates, `i` will be set to A.length-1, A[1 ... i] will be sorted and A[i] will be the smallest number in A[i ... A. length] due to the maitanance quality. Therefore A[1 ... A.length] will be fully sorted.

 __d.__ The worst case running time of bubblesort is O(n^2). Specifically `(n-1)((n-1)/2)` loop iterations will occur.
 
## 2-3) Correctness of Horners Rule

### Question

The following code fragment implements Horner's rule for evaluating a polynomial:

```
P(x) = Sum(k=0, n)(ak*x^k) 
		 = a0 + x(a1 + x(a2 + ... + x(a(n-1) + xan) ... ))

```

given the coefficients a0, a1, ... , a(n-1), an and a value for x:

```
y = 0
for i = n downto 0
	y = ai + x * y
```

__a.__ In terms of Θ-notation, what is the running time of this code fragment for Horner's rule?

__b.__ Write psuedocode to implement the naive polynomial-evaluation algorithm that computes each term of the polynomial from scratch. What is the running time of this algorithm? How does it compare to Horner's rule?

__c.__ Consider the following loop invariant:
	At the start of each iteration of the __for__ loop of lines 2-3,

	```
	y = Sum(k=0, n-(1+1))(a(k+i+1)*x^k)
	```
Interpret a summation with no terms as equaling 0. Following the structure of the loop invariant proof presented in this chapter, use this loop invariant to show that, at termination:

```
y = Sum(k=0, n)(ak*x^k)
```

__d.__ Conclude by arguing that the given code fragment correctly evaluates a polynomial characterized by the coefficients `a0, a1, ... , an`

### Answers

__a.__ 
```
int horners_rule(int *a, int x, int k, int len) {
        if(k < len) {
                return a[k] + x * horners_rule(a, x, k+1, len);
        }
        return 0;
}
```
Θ(n)

__b.__ 
```
int naive(int *a, int x, int k, int len) {
        int i;
        if(k < len) {
                int xToK = 1;
								// Slow exponentiation.Could be improved by bitshfiting.
                for(i = 0; i < k; i++) {
                        xToK = xToK * x;
                }
                return a[k] * xToK + naive(a, x, k+1, len);
        }
        return 0;
}
```
Techincally, this is Θ(n^2), but a fast exponentiation by squaring would give us Θ(nlgn). It is still slower than Horners either way.

__c.__ 

Base case: At the start of the loop, `y=0`. Since a summation of no terms = 0, the invariant holds

Induction: Assume the invariant holds for some `i`. 

```
y = ai + x * Sum(k=0, n-(i+1))(a(k+i+1))x^k 
	= ai + x * Sum(k=1,n-1)(a(k+i)*x^(k-1)
  = Sum(k=0, n-1)(a(k+i)*x^k))
```
At termination, i=0 so the sum at i=0 is the desired result by definition of polynomial

__d.__ The definition of polynomial is equal to the termination of the loop (i=0), therefore the algorithm is correct


## 2-4 Inversions

### Question 
Let `A[1..n]` be an array of n distinc numbers. If `i < j` and `A[i] > A[j]`, then the pair `(i, j)` is called an inversion of Assume

__a.__ List the five inversions of the array <2, 3, 8, 6, 1>

__b.__ What array with elements from the set {1,2,...,n} has the most inversions? How many does it have?

__c.__ What is the relationship between the running time of insertion sort and the number of inversions in the input array? Justify your answers

__d.__ Give an algorithm that determinse the number of inversions in any permutation on n elements in O(nlgn) worst-case time. (Hint: Modify merge sort)

### Answers

__a.__ (2,1), (3,1), (8,1), (8, 6), (6, 1)

__b.__ [n, n-1, ... 1]. It has n(n-1)/2 inversions

__c.__ Every inversion requires a swap in the insertion sort algorithm, so the running time of insertion sort in terms of constant time operations is the number of inversions the array has.

__d.__
[inversions.c](./inversions.c)
```C
int mergeAndCount(int *A, int p, int q, int r) {
        int sum = 0;
        int i, lInd, rInd;

        int lenLeft = q - p;
        int left[lenLeft + 1];
        for(i = 0; i < lenLeft; i++) {
                left[i] = A[p + i];
        }
        left[lenLeft] = 2147483647;

        int lenRight = r - q;
        int right[lenRight + 1];
        for(i = 0; i < lenRight; i++) {
                right[i] = A[q + i];
        }
        right[lenRight] = 2147483647;

        lInd = 0;
        rInd = 0;

        for(i = 0; i < lenLeft + lenRight; i++) {
                if(left[lInd] <= right[rInd]) {
                        A[p + i] = left[lInd];
                        lInd++;
                } else {
                        A[p + i] = right[rInd];
                        rInd++;
                        sum = sum + (lenLeft - lInd);
                }
        }
        return sum;
}

int inversions(int *A, int p, int r) {
        int sum = 0;
        if(r-p > 1) {
                int q = (r+p)/2;
                sum = sum + inversions(A, p, q);
                sum = sum + inversions(A, q, r);
                sum = sum + mergeAndCount(A, p, q, r);
        }
        return sum;
}
```

## 3.1 Exercises

### 3.1-1

#### Question
Let f(n) and g(n) be asymptotically nonnegative functions. Using the basic definition of θ-notation, prove that `max(f(n), g(n)) = θ(f(n) + g(n))`

#### Answer
By definition, `max(f(n), g(n) = θ(f(n) + g(n))` means `c1*(f(n)+g(n)) <= max(f(n), g(n)) <= c2*f(n)+g(n)` for some c1, c2, and all n > n0.

Choosing c1 = 0.5 and c2 = 100, this becomes

0.5 * (f(n) + g(n)) <= 0.5(max(f(n), g(n)) + max(f(n), g(n))) = max(f(n), g(n)) <= max(f(n), g(n)) + min(f(n), g(n)) = f(n) + g(n)

Since max(f(n), g(n)) + max(f(n), g(n)) will select the max function twice, it neccisarily has to be <= to max(f(n), g(n)) and therefore the inequality holds and `max(f(n), g(n)) = θ(f(n) + g(n))` 

I feel bad after looking up the answer. I won't do that again

### 3.1-2

#### Question
Show that for any real constants `a` and `b`, where `b > 0`, `(n + a)^b = θ(n^b)`

#### Answer

In order for `(n + a)^b = θ(n^b)` to be true, the following inequality must hold for some constant c1, c2, for all n > some n0, and for all a and all b > 0

`c1 * n^b <= (n + a)^b <= c2 * n^b`

Working on the left side first

```
c1 * n^b <= (n + a)^b
c1 * n^b <= n^b + a^b
c1 <= 1 + a^b/n^b
```

As n approaches infinity, the second addition term n the right hand side tends to 0 so c becomes a constant for large n. If one substitues n0 for n in the equation, then a correct constant c1 could be chosen to satisfy the inequality


Now working on the right side
```
(n + a)^b <= c2 * n^b
n^b + a^b <= c2 * n^b
1 + a^b/n^b <= c2
```

Again, c2 can be a constant because a^b/n^b trends to 0 as n approaches infinity. A proper c2 can be chosen by substituting n0 for n.

### 3.1-3

#### Question
Explain why the statement, "The running time of algorithm A is at least O(n^2), " is meaningless.

#### Answer
This statement says: `A <= N where N >= c * n^2 for some c and all n > n0`. The `>=` part comes from the "at least" terminology. N does not have an upper bound, so therefore using N as an upper bound is as meaningless as using infinity as an upper bound.

After I answered the question I checked my work by looking up the answer on the same rutgers site I cheated on 3.1-1 with. Ironically, the answer on the site was wrong. I'm not even going to use it to check my work.

### 3.1-4

#### Question

Is `2^(n+1) = O(2^n)`? Is `2^2n = O(2^n)`?

#### Answer
1) Yes, because choosing `c` to be 2 means 
```
2^(n+1) = c*2^n
2^(n+1) = 2*2^n
2^(n+1) = 2^(n+1)
```

2) No 
```
2^2n <= c * 2^n
2^n * 2^n <= c * 2^n
c >= 2^n
```
c is a function of n and therefore can not be constant

### 3.1-5

#### Question

Prove Theorem 3.1:

For any two functions `f(n)` and `g(n)`, we have `f(n) = θ(g(n))` if and only if `f(n) = O(g(n))` and `f(n) = Ω(g(n))`


#### Answer

By definition `f(n) = θ(g(n))` means that for some constants c1, c2, n0, for all n > n0 the following inequality holds:

```
c1*g(n) <= f(n) <= c2*g(n)
```

I will prove theorem 3.1 by showing that combination of definitions `f(n) = O(g(n))` and `f(n) = Ω(g(n))` renders the exact same inequality.

```
f(n) = O(g(n)) implies for there exists constants c and n0, for all n > n0 the following inequality holds:
f(n) <= c*g(n)

f(n) = Ω(g(n)) implies for some constants c and n0, for all n > n0 the following inequality holds:
c*g(n) <= f(n)

Combining these 2 inequalities implies, for some constants c1, c2, n1, n2 for all n > max(n1, n2):
c1*g(n) <= f(n) <= c2*g(n)

This is the definition of f(n) = θ(g(n)) so 
f(n) = θ(g(n)) if and only if f(n) = O(g(n)) and f(n) = Ω(g(n))


*please help me with the n > max(n1, n2) part as this is the only thing different from the combination of the 2 inequalities and the definition of BigTheta. I know there is a theorem that allows me to reduce that `forall n > max(n1, n2)` but I am not sure what it is.
```

### 3.1-6

#### Question

Prove that the running time of an algorithm is  `θ(g(n))` if and only if its worst-case running time is O(g(n)) and its best-case running time is `Ω(g(n))`

#### Answer

```
f(n) = θ(g(n)) -> for some c1, c2 n0: for all n > n0:
	c1*g(n) <= f(n) <= c2*g(n) 

f(n) = O(g(n)) -> for some c, n0: for all n > n0:
	f(n) <= c*g(n)

f(n) = Ω(g(n)) -> for some c, n0: for all n > n0:
	c*g(n) <=	f(n)

taking the max of the n0s for O(g(n)) and Ω(g(n)) satisfies both, since for all n > each n0, the assertion holds and therefore n0 can be increased and still hold, but not neccisarily decreased. Usining this, O(g(n)) and  Ω(g(n)) can be combined

f(n) = Ω(g(n)) = O(g(n)) -> for some c1, c2, n0: for all n > n0:
	c1*g(n) <= f(n) <= c2*g(n)

This is the exact definition of θ(g(n)), so θ(g(n)) IFF Ω(g(n)) & O(g(n))
```

### 3.1-7c7

#### Questions
Prove that o(g(n)) intersect w(g(n)) is the empty set

```
f(n) = o(g(n)) means that for some c & n0: for all n > n0: 
	f(n) < c * g(n)

f(n) = w(g(n)) means that for some c & n0: for all n > n0:
	f(n) > c * g(n)

Combining these 2 means

c1 * g(n) < f(n) < c2 * g(n) for all n > n0

At the limit of n=infinity, c1 * g(n) == c2 * g(n).
Therefore the inequality could never hold at such large numbers
```

