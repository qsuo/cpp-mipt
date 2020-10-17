
#ifndef VECTOR_H
#define VECTOR_H

#include "common.h"

#include <array>
#include <iostream>

namespace space
{

template <size_t Dim>
class Vector
{
public:

    using Coordinates = std::array<double, Dim>;
    
    
    Vector(const Coordinates &coords);
    Vector(const Vector &vec);

    bool operator==(const Vector &vec) const;
    Vector &operator+=(const Vector &vec);
    Vector &operator-=(const Vector &vec);
    Vector &operator*=(double val);

    double& operator[](size_t index) { return coords_[index]; }
    const double& operator[](size_t index) const { return coords_[index]; }

    double length() const;
    Vector<Dim - 1> project(size_t axis) const;
    
    void dump() const;
private:
    
    Coordinates coords_;

};


template <size_t Dim>
Vector<Dim>::Vector(const Vector &vec): coords_(vec.coords_) 
{}

template <size_t Dim>
Vector<Dim>::Vector(const Coordinates &coords): coords_(coords)
{}

template <size_t Dim>
bool Vector<Dim>::operator==(const Vector &vec) const
{
    for(size_t i = 0; i < Dim; ++i)
    {
        if(!equal(coords_[i], vec.coords_[i]))
            return false;
    }

    return true;
}

template <size_t Dim>
Vector<Dim> &Vector<Dim>::operator+=(const Vector &vec)
{
    for(size_t i = 0; i < Dim; ++i)
        coords_[i] += vec.coords_[i];
    return *this;
}

template <size_t Dim>
Vector<Dim> &Vector<Dim>::operator-=(const Vector &vec)
{
    for(size_t i = 0; i < Dim; ++i)
        coords_[i] -= vec.coords_[i];
    return *this;
}

template <size_t Dim>
Vector<Dim> &Vector<Dim>::operator*=(double val)
{
    for(size_t i = 0; i < Dim; ++i)
        coords_[i] *= val;
    return *this;
}

template <size_t Dim>
double Vector<Dim>::length() const
{
    double plen = 0;
    for(size_t i = 0; i < Dim; ++i)
        plen += coords_[i] * coords_[i];

    return std::sqrt(plen);
}

template <size_t Dim>
Vector<Dim> operator+(const Vector<Dim> &lhs, const Vector<Dim> &rhs)
{
    Vector<Dim> tmp(lhs);
    tmp += rhs;
    return tmp;
}

template <size_t Dim>
Vector<Dim> operator-(const Vector<Dim> &lhs, const Vector<Dim> &rhs)
{
    Vector<Dim> tmp(lhs);
    tmp -= rhs;
    return tmp;
}

template <size_t Dim>
Vector<Dim> operator*(const Vector<Dim> &lhs, double rhs)
{
    Vector<Dim> tmp(lhs);
    tmp *= rhs;
    return tmp;
}

template <size_t Dim>
void Vector<Dim>::dump() const
{
    std::cout << "(";
    for(auto c : coords_)
        std::cout << c << ", ";
    std::cout << ")" << std::endl;
}

template <size_t Dim>
double dotProduct(const Vector<Dim> &lhs, const Vector<Dim> &rhs)
{
    double product = 0;
    for(size_t i = 0; i < Dim; ++i)
        product += lhs[i] * rhs[i];
    return product;
}

template <size_t Dim>
Vector<Dim - 1> Vector<Dim>::project(size_t axis) const
{
    std::array<double, Dim - 1> vector = {};
    for(size_t i = 0, j = 0; i < Dim; i++)
    {
        if(i == axis)
            continue;
        vector[j++] = coords_[i];
    }
    return vector;
}


Vector<3> crossProduct(const Vector<3> &lhs, const Vector<3> &rhs);
Vector<3> crossProduct(const Vector<2> &lhs, const Vector<2> &rhs);

double pseudoProduct(const Vector<2> &lhs, const Vector<2> &rhs);

}// namespace space


#endif
