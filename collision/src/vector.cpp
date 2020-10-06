
#include "vector.h"

#include "common.h"

#include <iostream>
#include <cmath>

namespace space
{


Vector::Vector(const Vector &vec):
    x_(vec.x_), y_(vec.y_), z_(vec.z_) {}


bool Vector::operator==(const Vector &vec) const
{
    return ((std::abs(x_ - vec.x_) < EPS) &&
            (std::abs(y_ - vec.y_) < EPS) &&
            (std::abs(z_ - vec.z_) < EPS));
}

Vector Vector::operator+(const Vector &vec)
{
    return Vector(x_ + vec.x_,
                  y_ + vec.y_,
                  z_ + vec.z_);
}

Vector &Vector::operator+=(const Vector &vec)
{
    x_ += vec.x_;
    y_ += vec.y_,
    z_ += vec.z_;
    return *this;
}

Vector Vector::operator-(const Vector &vec)
{
    return Vector(x_ - vec.x_,
                  y_ - vec.y_,
                  z_ - vec.z_);
}

Vector &Vector::operator-=(const Vector &vec)
{
    x_ -= vec.x_;
    y_ -= vec.y_,
    z_ -= vec.z_;
    return *this;
}

Vector Vector::operator*(double val)
{
    return Vector(x_ * val,
                  y_ * val,
                  z_ * val);
}

Vector &Vector::operator*=(double val)
{
    x_ *= val;
    y_ *= val,
    z_ *= val;
    return *this;
}

double Vector::length() const
{
    double len = std::sqrt(x_ * x_ +
                           y_ * y_ +
                           z_ * z_);
    return len;
}

double Vector::dotProduct(const Vector &vec) const
{
    double product = x_ * vec.x_ +
                    y_ * vec.y_ +
                    z_ * vec.z_;
    return product;
}


Vector Vector::crossProduct(const Vector &vec) const
{
    double x = y_ * vec.z_ - z_ * vec.y_;
    double y = z_ * vec.x_ - x_ * vec.z_;
    double z = x_ * vec.y_ - y_ * vec.x_;
    return Vector(x, y, z);
}

void Vector::dump() const
{
    std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl;
}

} //namespace space
