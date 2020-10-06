
#ifndef VECTOR_H
#define VECTOR_H


namespace space
{

class Vector
{

public:

    Vector(): x_(0), y_(0), z_(0) {}
    
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

    void dump() const;

private:

    double x_;
    double y_;
    double z_;

};

}//namespace space

#endif
