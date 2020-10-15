
#ifndef VECTOR_H
#define VECTOR_H

#include "common.h"

#include <array>
#include <iostream>

namespace space
{

template <size_t Vsize>
class Vector
{
public:

    using Coordinates = std::array<double, Vsize>;
    
    
    Vector(const Coordinates &coords);
    Vector(const Vector &vec);

    bool operator==(const Vector &vec) const;
    Vector operator+(const Vector &vec);
    Vector &operator+=(const Vector &vec);
    Vector operator-(const Vector &vec);
    Vector &operator-=(const Vector &vec);
    Vector operator*(double val);
    Vector &operator*=(double val);
    
    //TODO replace
    double& operator[](size_t index) { return coords_[index]; }
    const double& operator[](size_t index) const { return coords_[index]; }
     
    double length() const;
    
    Vector<Vsize - 1> project(size_t axis) const;
    //Vector crossProduct(const Vector &vec) const;
    //double pseudoProduct(const Vector &vec) const;

    //Vector projectX() const { return Vector(0, y_, z_); }
    //Vector projectY() const { return Vector(x_, 0, z_); }
    //Vector projectZ() const { return Vector(x_, y_, 0); }

    void dump() const;
private:
    
    Coordinates coords_;

};


template <size_t Vsize>
Vector<Vsize>::Vector(const Vector &vec): coords_(vec.coords_) 
{}

template <size_t Vsize>
Vector<Vsize>::Vector(const Coordinates &coords): coords_(coords)
{}

template <size_t Vsize>
bool Vector<Vsize>::operator==(const Vector &vec) const
{
    bool eq = true;
    for(size_t i = 0; i < coords_.size(); ++i)
    {
        if(!equal(coords_[i], vec.coords_[i]))
        {
            eq = false;
            break;
        }
    }
    return eq;
}

template <size_t Vsize>
Vector<Vsize> Vector<Vsize>::operator+(const Vector &vec)
{
    Coordinates coords = {};
    for(size_t i = 0; i < coords_.size(); ++i)
        coords[i] = coords_[i] + vec.coords_[i];
    return Vector(coords);
}

template <size_t Vsize>
Vector<Vsize> &Vector<Vsize>::operator+=(const Vector &vec)
{
    for(size_t i = 0; i < coords_.size(); ++i)
        coords_[i] += vec.coords_[i];
    return *this;
}

template <size_t Vsize>
Vector<Vsize> Vector<Vsize>::operator-(const Vector &vec)
{
    Coordinates coords = {};
    for(size_t i = 0; i < coords_.size(); ++i)
        coords[i] = coords_[i] - vec.coords_[i];
    return Vector(coords);
}

template <size_t Vsize>
Vector<Vsize> &Vector<Vsize>::operator-=(const Vector &vec)
{
    for(size_t i = 0; i < coords_.size(); ++i)
        coords_[i] -= vec.coords_[i];
    return *this;
}

template <size_t Vsize>
Vector<Vsize> Vector<Vsize>::operator*(double val)
{
    Coordinates coords = {};
    for(size_t i = 0; i < coords_.size(); ++i)
        coords[i] = coords_[i] * val;
    return Vector(coords);
}

template <size_t Vsize>
Vector<Vsize> &Vector<Vsize>::operator*=(double val)
{
    for(size_t i = 0; i < coords_.size(); ++i)
        coords_[i] *= val;
    return *this;
}

template <size_t Vsize>
double Vector<Vsize>::length() const
{
    double len = 0;
    for(size_t i = 0; i < coords_.size(); ++i)
        len += coords_[i] * coords_[i];

    return std::sqrt(len);
}

template <size_t Vsize>
void Vector<Vsize>::dump() const //TODO repalce .size() with Vsize
{
    std::cout << "(";
    for(auto c : coords_)
        std::cout << c << ", ";
    std::cout << ")" << std::endl;
}

template <size_t Vsize>
double dotProduct(const Vector<Vsize> &lhs, const Vector<Vsize> &rhs)
{
    double product = 0;
    for(size_t i = 0; i < Vsize; ++i)
        product += lhs[i] * rhs[i];
    return product;
}

template <size_t Vsize>
Vector<Vsize - 1> Vector<Vsize>::project(size_t axis) const
{
    std::array<double, Vsize - 1> vector = {};
    for(size_t i = 0, j = 0; i < Vsize; i++)
    {
        if(i == axis)
            continue;
        vector[j++] = coords_[i];
    }
    return vector;
}

namespace dim3
{

using Vector = Vector<3>;

Vector crossProduct(const Vector &lhs, const Vector &rhs);

}// namespace 3d

namespace dim2
{
    
using Vector = Vector<2>;

double pseudoProduct(const Vector &lhs, const Vector &rhs);

}// namespace 2d

}//namespace space


#endif
