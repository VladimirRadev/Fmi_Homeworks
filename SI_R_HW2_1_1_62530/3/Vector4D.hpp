#pragma once
#include <vector>
#include <string>


class Vector4D {
private:
    std::vector<double>elements;
    void initializeVector(const double& v1, const double& v2, const double& v3, const double& v4);
public:
    Vector4D();
    Vector4D(double, double, double, double);
    Vector4D(const Vector4D& rhs);
    Vector4D& operator=(const Vector4D& rhs);
    double& operator[](const int& index);
    Vector4D operator+(const Vector4D& rhs)const;
    Vector4D& operator+=(const Vector4D& rhs);
    Vector4D operator-(const Vector4D& rhs)const;
    Vector4D& operator-=(const Vector4D& rhs);
    Vector4D operator*(const Vector4D& rhs)const;
    Vector4D operator*(const double& num)const;
    Vector4D& operator*=(const Vector4D& rhs);
    Vector4D& operator*=(const double& num);
    Vector4D operator/(const Vector4D& rhs)const;
    Vector4D& operator/=(const Vector4D& rhs);
    bool operator==(const Vector4D& rhs)const;
    bool operator!=(const Vector4D& rhs)const;
    bool operator<(const Vector4D& rhs)const;
    bool operator>(const Vector4D& rhs)const;
    bool operator<=(const Vector4D& rhs)const;
    bool operator>=(const Vector4D& rhs)const;
    bool operator!()const;
    Vector4D operator-()const;


};