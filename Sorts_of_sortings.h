#ifndef MY_SOLUTIONS_SORTS_OF_SORTINGS_H
#define MY_SOLUTIONS_SORTS_OF_SORTINGS_H
#include <utility>
#include <iostream>

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

#endif //MY_SOLUTIONS_SORTS_OF_SORTINGS_H
