#ifndef MY_SOLUTIONS_SORTS_OF_SORTINGS_H
#define MY_SOLUTIONS_SORTS_OF_SORTINGS_H
#include <utility>
#include <iostream>
#include <ctime>

template <typename T>
void InsertSort(T A[], size_t n){ // Сортировка вставками
    T tmp;
    for (size_t i = 0; i < n; ++i) {
        tmp = A[i];
        size_t j;
        for (size_t j = i; j > 0; --j) {
            if (tmp < A[j-1]){
                A[j] = A[j -1];
            }else{
                break;
            }
        }
        if (i!=j){
            A[j] = tmp;
        }
    }
}

template <typename T> 
void InsertSortA(T A[], size_t n) { // Сортировка вставками Advanced
	T tmp;
	for (size_t j = 1; j < n; ++j) {
		int l = 0, r = j;
		int m;
		while (l < r) {
			m = l + (r - l) / 2;
			if (A[j] < A[m]) r = m - 1;
			else l = m + 1;
		}
		if (r >= 0) {
			if (A[j] < A[r]) --r;
		}
		if (j > r + 1) {
			tmp = A[j];
			for (size_t i = j; i > r + 1; --i) {
				A[i] = A[i - 1];
			}
			A[r + 1] = tmp;
		}
	}
}

template <typename T>
void ChooseSort(T A[], size_t n){ // Сортировка выбором
    for (size_t i = 0; i < n; ++i) {
        size_t k = i;
        for (size_t j = k+1; j < n; ++j) {
            if (A[j] < A[k]){
                k = j;
            }
        }
        if (k != i){
            std::swap(A[k], A[i]);
        }
    }
}

template <typename T>
void bubble_sort(T a[], size_t n){  // Сортировка пузырьком
    for (int i = 0; i < n-1; ++i) {
        bool isSorted = true;
        for (int j = n-1; j >i ; --j) {
            if (a[j] < a[j-1]){
                std::swap(a[j], a[j-1]);
                isSorted = false;
            }
        }
        if (isSorted)
            break;
    }
}

template <typename T>
void QuickSortR(T A[], size_t n) {
	int l = 0, r = n - 1;
	size_t pindex = l + (r - l) / 2;
	T p = A[pindex];
	int i = l, j = r;
	while (i < j) {
		while (A[i] < p) i++;
		while (A[j] > p) j--;
		if (i < j) std::swap(A[i], A[j]), ++i, --j;
		else if (i == j)++i, --j;
	}
	if (pindex < i) {
		if (i < r) QuickSortR(A + i, n - i);
		if (j > l) QuickSortR(A, j + 1);
	}
	else {
		if (j > l) QuickSortR(A, j + 1);
		if (i < r) QuickSortR(A + i, n - i);
	}
}

template <typename T>
void QuickSortS(T A[], size_t n) {
	int N = n; size_t sz = 1;
	while (N) {
		N >>= 1;
		++sz;
	}
	size_t* StackLeft = new size_t[sz];
	size_t* StackRight = new size_t[sz];
	int LastInStack = -1;
	++LastInStack; StackLeft[LastInStack] = 0; StackRight[LastInStack] = n - 1;
	while (LastInStack > -1) {
		size_t l = StackLeft[LastInStack], r = StackRight[LastInStack];
		--LastInStack;

		size_t pindex = l + (r - l) / 2;
		T p = A[pindex];
		size_t i = l, j = r;
		while (i < j) {
			while (A[i] < p) {
				i++;
			}
			while (A[j] > p) j--;
			if (i < j) {
				std::swap(A[i], A[j]);
				++i;--j;
			}
			else if (i == j) {
				i++;
				if(j)--j;
			}
		}
		if (pindex < i) {
			if (j > l) {
				++LastInStack; StackLeft[LastInStack] = l; StackRight[LastInStack] = j;
			}
			if (i < r) {
				++LastInStack; StackLeft[LastInStack] = i; StackRight[LastInStack] = r;
			}
		}
		else {
			if (i < r) {
				++LastInStack; StackLeft[LastInStack] = i; StackRight[LastInStack] = r;
			}
			if (j > l) {
				++LastInStack; StackLeft[LastInStack] = l; StackRight[LastInStack] = j;
			}
		}
	}
	delete[] StackLeft;
	delete[] StackRight;
}
#endif //MY_SOLUTIONS_SORTS_OF_SORTINGS_H
