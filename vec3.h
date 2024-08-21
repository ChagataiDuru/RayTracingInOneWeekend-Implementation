#ifndef VEC3_H
#define VEC3_H

#include <array>
#include <cmath>
#include <iostream>

class vec3 {
public:
    vec3() : data{ 0.0, 0.0, 0.0 } {}
    vec3(double x, double y, double z) : data{ x, y, z } {}

    double x() const { return data[0]; }
    double y() const { return data[1]; }
    double z() const { return data[2]; }

    vec3 operator-() const { return vec3{ -data[0], -data[1], -data[2] }; }

    double& operator[](size_t i) { return data[i]; }
    double operator[](size_t i) const { return data[i]; }

    vec3& operator+=(const vec3& v) {
        (data[0] += v.data[0], data[1] += v.data[1], data[2] += v.data[2]);
        return *this;
    }

    vec3& operator*=(double t) {
        (data[0] *= t, data[1] *= t, data[2] *= t);
        return *this;
    }

    vec3& operator/=(double t) {
        return *this *= (1.0 / t);
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    constexpr double length_squared() const {
        return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
    }

private:
    std::array<double, 3> data;
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3{ u[0] + v[0], u[1] + v[1], u[2] + v[2] };
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3{ u[0] - v[0], u[1] - v[1], u[2] - v[2] };
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3{ u[0] * v[0], u[1] * v[1], u[2] * v[2] };
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3{ t * v[0], t * v[1], t * v[2] };
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1.0 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3{ u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0] };
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

#endif // VEC3_H