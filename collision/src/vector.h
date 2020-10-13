
#ifndef VECTOR_H
#define VECTOR_H


namespace space
{

class Vector
{

public:

    Vector(double x, double y, double z):
        x_(x), y_(y), z_(z) {}

    Vector(const Vector &vec);

    bool operator==(const Vector &vec) const;
    Vector operator+(const Vector &vec);
    Vector &operator+=(const Vector &vec);
    Vector operator-(const Vector &vec);
    Vector &operator-=(const Vector &vec);
    Vector operator*(double val);
    Vector &operator*=(double val);

    double length() const;
    double dotProduct(const Vector &vec) const;
    Vector crossProduct(const Vector &vec) const;
    
    Vector projectX() const { return Vector(0, y_, z_); }
    Vector projectY() const { return Vector(x_, 0, z_); }
    Vector projectZ() const { return Vector(x_, y_, 0); }

    void dump() const;

private:

    double x_ = 0;
    double y_ = 0;
    double z_ = 0;

};

namespace planar
{

class Vector
{
public:

private:
    double x_ = 0;
    double y_ = 0;

};

} //namespace planar
}//namespace space





#endif
