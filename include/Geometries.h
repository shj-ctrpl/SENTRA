#pragma once

template <typename T>
class vector3
{
public:
    T x;
    T y;
    T z;

    
    vector3()
    {
        x = (T)0;
        y = (T)0;
        z = (T)0;
    }

    
    vector3(const T _x, const T _y, const T _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    
    vector3(const vector3<T>& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    // Utility operations
    
    vector3<T>& zero()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
        return *this;
    }


    
    vector3<T>& set(const T _x, const T _y, const T _z)
    {
        x = _x;
        y = _y;
        z = _z;
        return *this;
    }

    
    vector3<T>& normalize()
    {
        T n = norm();
        if (n) {
            x /= n;
            y /= n;
            z /= n;
        }
        return *this;
    }

    
    vector3<T> normalized() const
    {
        T n = norm();
        vector3<T> r(x / n, y / n, z / n);
        return r;
    }

    // Vector basic operations
    
    const T norm() const
    {
        return (T)sqrt(dot(*this));
    }

    
    const T sum() const
    {
        return x + y + z;
    }

    
    const T dot(const vector3<T>& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    
    const vector3<T>cross(const vector3<T>& v) const
    {
        return vector3<T>(
            (y * v.z) - (z * v.y),
            (z * v.x) - (x * v.z),
            (x * v.y) - (y * v.x)
            );
    }

    
    const vector3<T> abs() const
    {
        return vector3<T>(std::abs(x), std::abs(y), std::abs(z));
    }

    
    vector3<T>& operator= (const vector3<T>& v)
    {
        if (&v == this) {
            return *this;
        }
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        return *this;
    }

    // Scalar operations

    
    vector3<T> operator+ (const T s)
    {
        x += s;    y += s;    z += s;
        return *this;
    }

    
    vector3<T> operator- (const T s)
    {
        x -= s;    y -= s;    z -= s;
        return *this;
    }

    
    vector3<T> operator* (const T s)
    {
        x *= s;    y *= s;    z *= s;
        return *this;
    }

    
    vector3<T> operator/ (const T s)
    {
        x /= s;    y /= s;    z /= s;
        return *this;
    }
    
    // Binary Scalar operations
    
    friend vector3<T> operator+(const T s, const vector3<T>& v) {
        return v + s;
    }

    
    friend vector3<T> operator-(const T s, const vector3<T>& v) {
        return v - s;
    }

    
    friend vector3<T> operator*(const T s, const vector3<T>& v) {
        return v * s;
    }

    
    friend vector3<T> operator/(const T s, const vector3<T>& v) {
        return v / s;
    }

    // Scalar assignment operations
    
    vector3<T>& operator+= (const T s)
    {
        (*this) = (*this) + s;
        return *this;
    }

    
    vector3<T>& operator-= (const T s)
    {
        (*this) = (*this) - s;
        return *this;
    }

    
    vector3<T>& operator*= (const T s)
    {
        (*this) = (*this) * s;
        return *this;
    }

    
    vector3<T>& operator/= (const T s)
    {
        (*this) = (*this) / s;
        return *this;
    }

    // Vector3 operations
    
    vector3<T> operator+ (const vector3<T>& v)
    {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }

    
    vector3<T> operator- (const vector3<T>& v)
    {
        x -= v.x;    y -= v.y;    z -= v.z;
        return *this;
    }

    
    vector3<T> operator* (const vector3<T>& v)
    {
        x *= v.x;    y *= v.y;    z *= v.z;
        return *this;
    }

    
    vector3<T> operator/ (const vector3<T>& v)
    {
        x /= v.x;    y /= v.y;    z /= v.z;
        return *this;
    }

    // Binary Vector3 operations
    
    friend vector3<T> operator+ (const vector3<T>& v1, const vector3<T>& v2) {
        vector3<T> r(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
        return r;
    }

    
    friend vector3<T> operator- (const vector3<T>& v1, const vector3<T>& v2) {
        vector3<T> r(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
        return r;
    }

    
    friend vector3<T> operator* (const vector3<T>& v1, const vector3<T>& v2) {
        vector3<T> r(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
        return r;
    }

    
    friend vector3<T> operator/ (const vector3<T>& v1, const vector3<T>& v2) {
        vector3<T> r(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
        return r;
    }

    // Vector3 assignment operations
    
    vector3<T>& operator+= (const vector3<T>& v)
    {
        (*this) = (*this) + v;
        return *this;
    }

    
    vector3<T>& operator-= (const vector3<T>& v)
    {
        (*this) = (*this) - v;
        return *this;
    }

    
    vector3<T>& operator*= (const vector3<T>& v)
    {
        (*this) = (*this) * v;
        return *this;
    }

    
    vector3<T>& operator/= (const vector3<T>& v)
    {
        (*this) = (*this) / v;
        return *this;
    }

    // Vector3 compare operations
    
    bool operator< (const vector3<T>& v) {
        return (x < v.x) && (y < v.y) && (z < v.z);
    }

    
    bool operator> (const vector3<T>& v) {
        return (x > v.x) && (y > v.y) && (z > v.z);
    }

    
    bool operator<= (const vector3<T>& v) {
        return (x <= v.x) && (y <= v.y) && (z <= v.z);
    }

    
    bool operator>= (const vector3<T>& v) {
        return (x >= v.x) && (y >= v.y) && (z >= v.z);
    }

    
    bool operator== (const vector3<T>& v) {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }

    
    bool operator!= (const vector3<T>& v) {
        return (x != v.x) || (y != v.y) || (z != v.z);
    }

    // Binary Vector3 compare operations
    friend bool operator< (const vector3<T>& v1, const vector3<T>& v2) {
        return (v1.x < v2.x) && (v1.y < v2.y) && (v1.z < v2.z);
    }

    friend bool operator> (const vector3<T>& v1, const vector3<T>& v2) {
        return (v1.x > v2.x) && (v1.y > v2.y) && (v1.z > v2.z);
    }

    friend bool operator<= (const vector3<T>& v1, const vector3<T>& v2) {
        return (v1.x <= v2.x) && (v1.y <= v2.y) && (v1.z <= v2.z);
    }

    friend bool operator>= (const vector3<T>& v1, const vector3<T>& v2) {
        return (v1.x >= v2.x) && (v1.y >= v2.y) && (v1.z >= v2.z);
    }

    friend bool operator== (const vector3<T>& v1, const vector3<T>& v2) {
        return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
    }

    friend bool operator!= (const vector3<T>& v1, const vector3<T>& v2) {
        return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z);
    }
    // Type conversion
    template <typename U>
    operator vector3<U>() {
        return vector3<U>((U)x, (U)y, (U)z);
    }
};












