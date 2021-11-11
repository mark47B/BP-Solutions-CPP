#ifndef _MYSORTS_2020_
#define _MYSORTS_2020_


#include <utility>
#include <ctime>
#include <iostream>

template <typename T>
void BubbleSort(T A[], size_t n) {                        //O(n^2)

#ifdef _SORTSTAT                          1                //preddetermine const in debug "_DEBUG"
	unsigned long long c1 = 0, c2 = 0;
	clock_t tictoc = clock();
#endif

	for (size_t j = 0; j < (n - 1); ++j) {
		bool isSorted = 1;
		for (size_t i = (n - 1); i > j; --i) {
#ifdef _SORTSTAT
			++c1;
#endif
			if (A[i] < A[i - 1]) {
				std::swap(A[i], A[i - 1]);
#ifdef _SORTSTAT
				c2 += 3;
#endif
				isSorted = 0;
			}
		}
		if (isSorted)
			break;
	}


#ifdef _SORTSTAT
	tictoc = clock() - tictoc;
	std::cout << " <" << c1 << ", =" << c2 << ", tics: " << tictoc << std::endl;
#endif
}

template <typename T>
void ChooseSort(T A[], size_t n) {

#ifdef _SORTSTAT                                          //preddetermine const in debug "_DEBUG"
	unsigned long long c1 = 0, c2 = 0;
	clock_t tictoc = clock();
#endif

	for (size_t j = 0; j < n - 1; ++j) {
		size_t k = j;                              //index min
		for (size_t i = k + 1; i < n; ++i) {

#ifdef _SORTSTAT
			++c1;
#endif

			if (A[i] < A[k])
				k = i;
		}
		if (k != j) {
			std::swap(A[k], A[j]);

#ifdef _SORTSTAT
			c2 += 3;
#endif

		}
	}
#ifdef _SORTSTAT
	tictoc = clock() - tictoc;
	std::cout << " <" << c1 << ", =" << c2 << ", tics: " << tictoc << std::endl;
#endif
}

template <typename T>
void InsertSort(T A[], size_t n) {
#ifdef _SORTSTAT                                          //preddetermine const in debug "_DEBUG"
	unsigned long long c1 = 0, c2 = 0;
	clock_t tictoc = clock();
#endif
	T tmp;
	for (size_t j = 1; j < n; ++j) {
		tmp = A[j];
		size_t i;
		for (i = j; i > 0; --i) {
#ifdef _SORTSTAT
			c1++;
#endif
			if (tmp < A[i - 1]) {
#ifdef _SORTSTAT
				c2++;
#endif
				A[i] = A[i - 1];
			}
			else
				break;
		}
		if (i != j) {
			A[i] = tmp;

#ifdef _SORTSTAT
			c2++;
#endif
		}
	}
#ifdef _SORTSTAT
	tictoc = clock() - tictoc;
	std::cout << " <" << c1 << ", =" << c2 << ", tics: " << tictoc << std::endl;
#endif
}

template <typename T> 
void InsertSortA(T A[], size_t n) {
#ifdef _SORTSTAT                                          //preddetermine const in debug "_DEBUG"
	unsigned long long c1 = 0, c2 = 0;
	clock_t tictoc = clock();
#endif
	T tmp;
	for (size_t j = 1; j < n; ++j) {
		int l = 0, r = j;
		int m;
		while (l < r) {
#ifdef _SORTSTAT
			c1++;
#endif
			m = l + (r - l) / 2;
			if (A[j] < A[m]) r = m - 1;
			else l = m + 1;
		}
		if (r >= 0) {
#ifdef _SORTSTAT
			c1++;
#endif
			if (A[j] < A[r]) --r;
		}
		if (j > r + 1) {
#ifdef _SORTSTAT
			c2++;
#endif
			tmp = A[j];
			for (size_t i = j; i > r + 1; --i) {
#ifdef _SORTSTAT
				c2++;
#endif
				A[i] = A[i - 1];
			}
#ifdef _SORTSTAT
				c2++;
#endif
			A[r + 1] = tmp;
		}
	}
#ifdef _SORTSTAT
	tictoc = clock() - tictoc;
	std::cout << " <" << c1 << ", =" << c2 << ", tics: " << tictoc << std::endl;
#endif
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
#ifdef _SORTSTAT                                          //preddetermine const in debug "_DEBUG"
	unsigned long long c1 = 0, c2 = 0;
	clock_t tictoc = clock();
#endif
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
#ifdef _SORTSTAT
		c2++;
#endif
		size_t i = l, j = r;
#ifdef _SORTSTAT
		c1+=r-l+1;
#endif
		while (i < j) {
			while (A[i] < p) {
				i++;
			}
			while (A[j] > p) j--;
			if (i < j) {
				std::swap(A[i], A[j]);
#ifdef _SORTSTAT
				c2+=3;
#endif
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

#ifdef _SORTSTAT
	tictoc = clock() - tictoc;
	std::cout << " <" << c1 << ", =" << c2 << ", tics: " << tictoc << std::endl;
#endif
}

template<typename T>
void _Merge(T A[], size_t l, size_t m, size_t r, unsigned long long &c1, unsigned long long &c2) {
	size_t sz = r - l + 1;
	T* tmp = new T[sz];
	size_t s1 = l, e1 = m, s2 = m + 1, e2 = r;
	int ind = 0;
	while (s1 <= e1 && s2 <= e2) {
		if (A[s1] < A[s2]) {
			tmp[ind] = A[s1]; s1++;
		}
		else {
			tmp[ind] = A[s2]; s2++;
		}
		++c1; ++c2;
		ind++;
	}
	while (s1 <= e1) tmp[ind] = A[s1], s1++, ind++, c2++;
	while (s2 <= e2) tmp[ind] = A[s2], s2++, ind++, c2++;
	for (ind = 0; ind < sz; ind++) A[l + ind] = tmp[ind], c2++;
	delete[] tmp;
}
template<typename T>
void _Split(T A[], size_t l, size_t r, unsigned long long& c1, unsigned long long& c2) {
	if (l < r) {
		size_t m = l + (r - l) / 2;
		_Split(A, l, m, c1, c2);
		_Split(A, m + 1, r, c1,c2);
		_Merge(A, l, m, r, c1, c2);
	}
}
template <typename T> 
void MergeSort(T A[], size_t n) {
#ifdef _SORTSTAT                                          //preddetermine const in debug "_DEBUG"
	unsigned long long c1 = 0, c2 = 0;
	clock_t tictoc = clock();
#endif
	_Split(A, 0, n - 1, c1, c2);
#ifdef _SORTSTAT
	tictoc = clock() - tictoc;
	std::cout << " <" << c1 << ", =" << c2 << ", tics: " << tictoc << std::endl;
#endif
}
#endif