#ifndef MY_SOLUTIONS_MATRIX_H
#define MY_SOLUTIONS_MATRIX_H
// Изначальная идея - реализовать шаблон класса matrix, но в данном решении тип задан статически как double
// в связи с разделением объявления класса и его реализации

#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::cin;
using std::pow;

template<typename T>
class Matr {
private:
    int n, m;
    T **M;
public:
    Matr();
    Matr(int _m, int _n);
    Matr(const Matr &_M);
    T getMij(int i, int j);
    void SetMij(int i, int j, T value);
    void Print(const char *ObjName = "No name");
    void Transpose();
    void Rotate_90();
    void RandomFill();
    void SnailFill(); // Заполнение матрицы по спирали
    T Det(); // Определитель матрицы
    Matr Solution(Matr &B);
    void ToTrinagle();
    Matr ConcatR(Matr& B); // Конкатенация матриц
    Matr Minorij(int i, int j); //Минор элемента
    Matr operator=(const Matr &_M);
    const Matr operator+(const Matr &right);
    const Matr operator-(const Matr &right);
    const Matr operator*(const Matr<T> &right);
    ~Matr();
};

#endif //MY_SOLUTIONS_MATRIX_H
