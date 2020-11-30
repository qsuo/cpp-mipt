
#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <functional>
#include <iostream>

namespace alg
{

template <typename T>
class Matrix
{

public:

/************************************************************/

    struct Row
    {
        T *row;

        const T& operator[](int n) const { return row[n]; }
        T& operator[](int n)             { return row[n]; }
    };

/************************************************************/

    Matrix(size_t nrows, size_t ncols, T val = T());
    explicit Matrix(size_t n);
    
    template <typename It>
    Matrix(size_t nrows, size_t ncols, It begin, It end);
    
    ~Matrix();
    Matrix(const Matrix &rsh);
    static Matrix identity(size_t n);

/************************************************************/

    Matrix& operator=(const Matrix &rhs);
    
    //const   Row operator[](int n) const { return { buffer_[n] }; }
    Row operator[](int n) { return { buffer_[n] }; }

    Matrix& operator+= (const Matrix& rhs) &;
    Matrix& operator-= (const Matrix& rhs) &;
    Matrix& operator*= (T n) &;

/************************************************************/

    size_t nrows()  const   { return nrows_; }
    size_t ncols()  const   { return ncols_; }
    size_t size()   const   { return nrows_ * ncols_; }
    T **data()      const   { return buffer_; }

/************************************************************/
    
    T trace() const;
    bool equal(const Matrix &rhs) const;
    void dump() const;

/************************************************************/

    void swapRows(size_t i, size_t j);
    
    /*
    Matrix& negate() &;
    Matrix operator-() const;
    Matrix& transpose() &;
    Matrix& dotProduct(const Matrix& rhs) &;
    */

    //T determinant() const;

/************************************************************/

private:
   
    void allocateBuffer(size_t nrows, size_t ncols);

    size_t nrows_;
    size_t ncols_;

    T **buffer_ = nullptr;
    T *init_ = nullptr;

};

template <typename T>
bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs);

template <typename T>
Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs);

template <typename T>
Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs);

template <typename T>
Matrix<T> operator*(const Matrix<T> &lhs, T n);

    
template <typename T>
void Matrix<T>::allocateBuffer(size_t nrows, size_t ncols)
{
    buffer_ = new T*[nrows];
    buffer_[0] = new T[nrows * ncols];
    init_ = buffer_[0];
    for(size_t i = 1; i < nrows; i++)
        buffer_[i] = buffer_[i - 1] + ncols;
}

template <typename T>
Matrix<T>::Matrix(size_t nrows, size_t ncols, T val)
    : nrows_(nrows), ncols_(ncols)
{
    allocateBuffer(nrows_, ncols_);
    for(size_t i = 0; i < nrows_; i++)
    {
        for(size_t j = 0; j < ncols_; j++)
            buffer_[i][j] = T(val);
    }
}

template <typename T>
Matrix<T>::Matrix(size_t n): Matrix(n, n)
{
}

template <typename T>
template <typename It>
Matrix<T>::Matrix(size_t nrows, size_t ncols, It begin, It end)
    : nrows_(nrows), ncols_(ncols)
{
    allocateBuffer(nrows_, ncols_);
    auto it = begin;
    for(size_t i = 0; i < nrows_; i++)
    {
        for(size_t j = 0; j < ncols_; j++)
        {
            buffer_[i][j] = T(*it++);
            if(it == end)
                return;
        }
    }

}

template <typename T>
Matrix<T>::Matrix(const Matrix &rhs)
    : nrows_(rhs.nrows_), ncols_(rhs.ncols_)
{
    allocateBuffer(nrows_, ncols_);
    for(size_t i = 0; i < nrows_; i++)
    {
        for(size_t j = 0; j < ncols_; j++)
            buffer_[i][j] = T(rhs.buffer_[i][j]);
    }
}

template <typename T>
Matrix<T> Matrix<T>::identity(size_t n)
{
    Matrix I(n);
    for(size_t i = 0; i < n; i++)
        I[i][i] = T(1);
    return I;
}


template <typename T>
Matrix<T>::~Matrix()
{
    delete [] init_;
    delete [] buffer_;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix &rhs)
{
    if(this == &rhs)
        return *this;
    
    for(size_t i = 0; i < nrows_; i++)
        for(size_t j = 0; j < ncols_; j++)
            buffer_[i][j] = rhs.buffer_[i][j];
    
    return *this;
}

template <typename T>
bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs)
{
    return lhs.equal(rhs);
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix& rhs) &
{
    for(size_t i = 0; i < nrows_; i++)
        for(size_t j = 0; j < ncols_; j++)
            buffer_[i][j] += rhs.buffer_[i][j];

    return *this;
}

template <typename T>
Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> tmp(lhs);
    tmp += rhs;
    return tmp;
}


template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix& rhs) &
{
    for(size_t i = 0; i < nrows_; i++)
        for(size_t j = 0; j < ncols_; j++)
            buffer_[i][j] -= rhs.buffer_[i][j];

    return *this;
}

template <typename T>
Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> tmp(lhs);
    tmp -= rhs;
    return tmp;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(T n) &
{
    for(size_t i = 0; i < nrows_; i++)
        for(size_t j = 0; j < ncols_; j++)
            buffer_[i][j] *= n;

    return *this;
}

template <typename T>
Matrix<T> operator*(const Matrix<T> &lhs, T n)
{
    Matrix<T> tmp(lhs);
    tmp *= n;
    return tmp;
}

template <typename T>
bool Matrix<T>::equal(const Matrix &rhs) const
{
    for(size_t i = 0; i < nrows_; i++)
    {
        for(size_t j = 0; j < ncols_; j++)
            if(!(buffer_[i][j] == rhs.buffer_[i][j]))
                return false;
    }
    return true;
}

template <typename T>
void Matrix<T>::swapRows(size_t i, size_t j)
{
    std::swap(buffer_[i], buffer_[j]);
}


template <typename T>
T Matrix<T>::trace() const
{
    T tmp(buffer_[0][0]);
    for(size_t i = 1; i < nrows_; i++)
        tmp = tmp + buffer_[i][i];
    return tmp;
}

template <typename T>
void Matrix<T>::dump() const
{
    for(size_t i = 0; i < nrows_; i++)
    {
        for(size_t j = 0; j < ncols_; j++)
            std::cout << buffer_[i][j] << " ";
        std::cout << std::endl;
    }
}

template < typename T, class Compare = std::equal_to<T> >
T determinant(const Matrix<T> &matrix)
{
    Compare comparator;
    Matrix<T> triangle(matrix);

    
    for(size_t i = 0; i < triangle.nrows(); i++)
    {
        size_t row = i;
        bool swap = false;
        for(row = i; row < triangle.nrows(); row++)
        {
            if(!comparator(triangle[i][row], T(0)) && i != row)
            {
                swap = true;
                break;
            }
        }

        if(swap)
            triangle.swapRows(i, row);

        for(size_t j = i + 1; j < triangle.nrows(); j++)
        {
            auto m1 = triangle[j][i];
            auto m2 = triangle[i][i];
            for(size_t k = i; k < triangle.ncols(); k++)
                triangle[j][k] -= triangle[i][k] / m2 * m1;
        }
    }

    T det(1);
    for(size_t i = 0; i < triangle.nrows(); i++)
        det *= triangle[i][i];
    return det;

}

}// namespace alg
#endif
