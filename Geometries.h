#ifndef VECTOR3
#define VECTOR3

#include <cmath>

template<class T>
class vector3
{
public:
    T x;
    T y;
    T z;

    // Constructors & Destructors
    vector3();
    vector3(const T x, const T y, const T z);
    vector3(const vector3<T>& v);
    ~vector3() = default;

    // utility operations
    vector3<T>& zero();
    vector3<T>& set(const T x, const T y, const T z);
    vector3<T>& normalize();
    vector3<T> normalized() const;

    // Vector basic operations
    const T norm() const;
    const T sum() const;
    const T dot(const vector3<T>&) const;
    const vector3<T> cross(const vector3<T>&) const;
    const vector3<T> abs() const;
    vector3<T>& operator= (const vector3<T>& v);

    // Scalar operations
    vector3<T> operator+(const T s);
    vector3<T> operator-(const T s);
    vector3<T> operator*(const T s);
    vector3<T> operator/(const T s);
    
    // Binary Scalar operations
    friend vector3<T> operator+(const T s, const vector3<T>& v);
    friend vector3<T> operator-(const T s, const vector3<T>& v);
    friend vector3<T> operator*(const T s, const vector3<T>& v);
    friend vector3<T> operator/(const T s, const vector3<T>& v);

    // Scalar assignment operations
    vector3<T>& operator+=(const T s);
    vector3<T>& operator-=(const T s);
    vector3<T>& operator*=(const T s);
    vector3<T>& operator/=(const T s);

    // Vector3 operations
    vector3<T> operator+(const vector3<T>& s);
    vector3<T> operator-(const vector3<T>& s);
    vector3<T> operator*(const vector3<T>& s);
    vector3<T> operator/(const vector3<T>& s);

    // Binary Vector3 operations
    friend vector3<T> operator+(const vector3<T>& v1, const vector3<T>& v2);
    friend vector3<T> operator-(const vector3<T>& v1, const vector3<T>& v2);
    friend vector3<T> operator*(const vector3<T>& v1, const vector3<T>& v2);
    friend vector3<T> operator/(const vector3<T>& v1, const vector3<T>& v2);

    // Vector3 assignment operations
    vector3<T>& operator+=(const vector3<T>& v);
    vector3<T>& operator-=(const vector3<T>& v);
    vector3<T>& operator*=(const vector3<T>& v);
    vector3<T>& operator/=(const vector3<T>& v);

    // Vector3 compare operations
    bool operator< (const vector3<T>& v);
    bool operator> (const vector3<T>& v);
    bool operator<= (const vector3<T>& v);
    bool operator>= (const vector3<T>& v);
    bool operator== (const vector3<T>& v);
    bool operator!= (const vector3<T>& v);

    // Binary Vector3 compare operations
    friend bool operator< (const vector3<T>& v1, const vector3<T>& v2);
    friend bool operator> (const vector3<T>& v1, const vector3<T>& v2);
    friend bool operator<= (const vector3<T>& v1, const vector3<T>& v2);
    friend bool operator>= (const vector3<T>& v1, const vector3<T>& v2);
    friend bool operator== (const vector3<T>& v1, const vector3<T>& v2);
    friend bool operator!= (const vector3<T>& v1, const vector3<T>& v2);

    // Type conversion
    template<class U>
    operator vector3<U>() {
        return vector3<T>((T)U.x, (T)U.y, (T)U.z);
    }
};

#endif