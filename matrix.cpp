#include "matrix.h"

template
class Matr<double>;

template<typename T>
Matr<T>::Matr() {
    n = m = 0;
    M = nullptr;
}

template<typename T>
Matr<T>::Matr(int _m, int _n) {
    m = _m;
    n = _n;
    M = (T **) new T *[m];
    for (int i = 0; i < m; i++) {
        M[i] = (T *) new T[n];
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = T(0);
        }
    }
}

template<typename T>
Matr<T>::Matr(const Matr &_M) {
    m = _M.m;
    n = _M.n;

    M = (T **)
            new T *[m];

    for (int i = 0; i < m; i++)
        M[i] = (T *)
                new T[n];

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = _M.M[i][j];
}

template<typename T>
T Matr<T>::getMij(int i, int j) {
    if ((m > 0) && (n > 0) && (i <= this->m) && (j <= this->n))
        return M[i][j];
    else
        return 0;
}

template<typename T>
void Matr<T>::SetMij(int i, int j, T value) {
    if ((i < 0) || (i >= m)) {
        return;
    }
    if ((j < 0) || (j >= n))
        return;
    M[i][j] = value;
}

template<typename T>
void Matr<T>::Print(const char *ObjName) {
    cout << "Object: " << ObjName << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << M[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "---------------------" << endl << endl;
}


template<typename T>
void Matr<T>::Transpose() {
    Matr<T> temp(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            temp.SetMij(i, j, M[j][i]);
        }
    }
    *this = temp;
}

template<typename T>
void Matr<T>::Rotate_90() {
    Matr<T> temp(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            temp.SetMij(i, m - (1 + j), M[j][i]);
        }
    }
    *this = temp;
}

template<typename T>
void Matr<T>::RandomFill() {
    srand(time(0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            M[i][j] = (double) ((rand()) % 101);
        }
    }
}

template<typename T>
void Matr<T>::SnailFill() {
    int i = 0, j = 0;
    int k = 1;
    for (int c = 0; (c <= n - c) || (c + 1 <= m - c) || (n - (c + 2) >= c) || (m - (c + 2) >= c + 1); c++) {
        if (c >= n - c)
            break;
        for (j = c; j < n - c; ++j) {
            M[i][j] = (double) k++;
        }
        --j;
        if (c + 1 >= m - c)
            break;
        for (i = c + 1; i < m - c; ++i) {
            M[i][j] = (double) k++;
        }
        --i;
        if (n - (c + 2) < c)
            break;
        for (j = n - (c + 2); j >= c; --j) {
            M[i][j] = (double) k++;
        }
        ++j;
        if (m - (c + 2) < c + 1)
            break;
        for (i = m - (c + 2); i >= c + 1; --i) {
            M[i][j] = (double) k++;
        }
        ++i;
    }
}


template<typename T>
T Matr<T>::Det() {
    if (n != m) {
        cout << "Для поиска определителя матрицы, размерность должна быть nxn";
        return 0.0;
    }
    if (n == 1) {
        return M[0][0];
    }
    if (n == 2) {
        return M[0][0] * M[1][1] - M[0][1] * M[1][0];
    }
    Matr<double> _M;
    T sum;
    for (int i = 0; i < n; ++i) {
        sum += pow(-1.0, 0 + i) * M[0][i] * ((this->Minorij(0, i)).Det());
    }
    return sum;
}

template<typename T>
Matr<T> Matr<T>::Solution(Matr<T> &B) {
    if (this->Det() == 0) { throw "Определитель = 0"; }
    if (B.m != m || B.n != 1) { throw "Размерность матрицы B не соответсвует требуемым параметрам"; }
    Matr A;
    int s = this->m, c = n + B.n;
    T factor;
    try {
        A = this->ConcatR(B);
    }
    catch (const char *error) {
        cout << "Ошибка: " << error << endl;
    }
    for (int i = 0; i < m; ++i) { //  прямой ход
        for (int j = i + 1; j < m; ++j) {
            factor = A.getMij(j, i)/A.getMij(i,i);
            for (int k = 0; k < c; ++k) {
                A.SetMij(j, k, A.getMij(j, k) - A.getMij(i, k)*factor);
            }

        }
    }
    Matr X(m, 1); // Создаём столбец значений x1, x2 и т.д
    for (int i = m - 1; i >= 0; --i) { // Обратный ход
        factor = 0;
        for (int j = i + 1; j < n; ++j) {
            factor += A.getMij(i, j) * X.getMij(j, 0);
        }
        X.SetMij(i, 0, (A.getMij(i, c - 1) - factor)/A.getMij(i, i));
    }
    return X;

}

template <typename T>
void Matr<T>::ToTrinagle() {
    T factor = 0.;
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            factor = M[j][i]/M[i][i];
            for (int k = 0; k < n; ++k) {
                M[j][k] = round((M[j][k] - M[i][k]*factor)*10e3)/10e3;
            }
        }
    }
}

template <typename T>
Matr<T> Matr<T>::ConcatR(Matr& B){
    if (B.m != this->m)
    {
        throw "Dim. matrix are different";
    }

    int a = this->m, b = this->n;
    Matr A(a, b + B.n); // Создаём матрицу размера m x (n + B.n)
    for (int i = 0; i < a; ++i) { // Записываем исходную матрицу в A
        for (int j = 0; j < b; ++j) {
            A.SetMij(i, j, M[i][j]);
        }
    }
    for (int i = 0; i < B.m; ++i) {
        for (int j = 0; j < B.n; ++j) {
            A.SetMij(i, b + j, B.getMij(i, j));
        }
    }
    return A;
}
template<typename T>
Matr<T> Matr<T>::Minorij(int i, int j) {
    Matr<T> _M(m - 1, n - 1);
    int t = 0, r = 0;
    for (int k = 0; k < m; ++k) {
        if (k == i) {
            continue;
        }
        for (int l = 0; l < n; ++l) {
            if (l == j) {
                continue;
            }
            _M.SetMij(t, r, M[k][l]);
            ++r;
        }
        ++t;
        r = 0;
    }
    return _M;
}

template<typename T>
Matr<T> Matr<T>::operator=(const Matr &_M) {
    if (this == &_M) {
        return *this;
    }
    if (n > 0) {
        for (int i = 0; i < m; i++)
            delete[] M[i];
    }

    if (m > 0) {
        delete[] M;
    }

    m = _M.m;
    n = _M.n;

    M = (T **)
            new T *[m];
    for (int i = 0; i < m; i++)
        M[i] = (T *)
                new T[n];

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = _M.M[i][j];

    return *this;
}


template<typename T>
const Matr<T> Matr<T>::operator+(const Matr &right) {
    Matr temp(m, right.n);
    if ((m != right.m) || (n != right.n)) {
        cout << "Для сложения размерности матриц должны быть одинаковыми!!!" << endl;
        return temp;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; ++j) {
            temp.SetMij(i, j, M[i][j] + right.M[i][j]);
        }
    }

    return temp;
}

template<typename T>
const Matr<T> Matr<T>::operator-(const Matr &right) {
    Matr temp(m, right.n);
    if ((m != right.m) || (n != right.m)) {
        cout << "Для сложения размерности матриц должны быть одинаковыми!!!" << endl;
        return temp;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; ++j) {
            temp.SetMij(i, j, M[i][j] - right.M[i][j]);
        }
    }
    return temp;
}

template<typename T>
const Matr<T> Matr<T>::operator*(const Matr<T> &right) {
    Matr<T> temp(m, right.n);
    if (n != right.m) {
        cout << "Для умножения матриц число столбцов левой матрицы должно быть равно числу строк правой!!!" << endl;
        return temp;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; ++j) {
            for (int r = 0; r < n; ++r) {
                temp.SetMij(i, j, temp.getMij(i, j) + M[i][r] * right.M[r][j]);
            }
        }
    }
    return temp;
}

template<typename T>
Matr<T>::~Matr() {
    if (n > 0) {
        for (int i = 0; i < m; i++) {
            delete[] M[i];
        }
    }
    if (m > 0) {
        delete[] M;
    }
}
