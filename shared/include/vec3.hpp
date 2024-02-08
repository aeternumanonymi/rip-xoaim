#ifndef VEC3_H
#define VEC3_H

#include <type_traits>
#include <stdexcept>
#include <array>
#include <cmath>

namespace math
{
    class vec3
    {
    public:
        float x, y, z;

        vec3() : x(0.0f), y(0.0f), z(0.0f) {}

        vec3(float x, float y, float z) : x(x), y(y), z(z) {}

        vec3(const vec3 &v) noexcept : x(v.x), y(v.y), z(v.z) {}

        float &operator[](size_t index)
        {
            if (index == 0)
                return x;
            else if (index == 1)
                return y;
            else if (index == 2)
                return z;
            else
                throw std::out_of_range("Index out of range in vec3 subscript operator.");
        }

        const float &operator[](size_t index) const
        {
            if (index == 0)
                return x;
            else if (index == 1)
                return y;
            else if (index == 2)
                return z;
            else
                throw std::out_of_range("Index out of range in vec3 subscript operator.");
        }

        vec3 &operator=(const vec3 &v) noexcept
        {
            x = v.x;
            y = v.y;
            z = v.z;
            return *this;
        }

        vec3 &operator+=(const vec3 &v) noexcept
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        vec3 &operator-=(const vec3 &v) noexcept
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        bool operator==(const vec3 &v) const noexcept
        {
            return (x == v.x) && (y == v.y) && (z == v.z);
        }

        bool operator!=(const vec3 &v) const noexcept
        {
            return !(*this == v);
        }

        vec3 operator+(const vec3 &v) const noexcept
        {
            return vec3(x + v.x, y + v.y, z + v.z);
        }

        vec3 operator-(const vec3 &v) const noexcept
        {
            return vec3(x - v.x, y - v.y, z - v.z);
        }

        vec3 &operator*=(const vec3 &v) noexcept
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }

        vec3 &operator/=(const vec3 &v) noexcept
        {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            return *this;
        }

        vec3 operator*(const vec3 &v) const noexcept
        {
            return vec3(x * v.x, y * v.y, z * v.z);
        }

        vec3 operator/(const vec3 &v) const noexcept
        {
            return vec3(x / v.x, y / v.y, z / v.z);
        }

        vec3 &operator*=(float scalar) noexcept
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        vec3 &operator/=(float scalar) noexcept
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        vec3 operator*(float scalar) const noexcept
        {
            return vec3(x * scalar, y * scalar, z * scalar);
        }

        vec3 operator/(float scalar) const noexcept
        {
            return vec3(x / scalar, y / scalar, z / scalar);
        }

        vec3 &operator+=(float scalar) noexcept
        {
            x += scalar;
            y += scalar;
            z += scalar;
            return *this;
        }

        vec3 &operator-=(float scalar) noexcept
        {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            return *this;
        }

        vec3 operator+() const noexcept
        {
            return vec3(x, y, z);
        }

        vec3 operator-() const noexcept
        {
            return vec3(-x, -y, -z);
        }

        bool operator==(float value) const noexcept
        {
            return (x == value) && (y == value) && (z == value);
        }

        bool operator!=(float value) const noexcept
        {
            return (x != value) || (y != value) || (z != value);
        }

        float length() const noexcept
        {
            return std::sqrt(length_3d_sqr());
        }

        float length_3d_sqr() const noexcept
        {
            return x * x + y * y + z * z;
        }

        vec3 normalized() const
        {
            float len = length();
            if (len != 0.0f)
                return *this / len;
            return *this;
        }

        void normalize()
        {
            float len = length();
            if (len != 0.0f)
            {
                x /= len;
                y /= len;
                z /= len;
            }
        }

        float dot_product(const vec3 &v) const noexcept
        {
            return x * v.x + y * v.y + z * v.z;
        }

        vec3 cross_product(const vec3 &v) const noexcept
        {
            return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
        }

        bool is_zero() const noexcept
        {
            return x == 0.0f && y == 0.0f && z == 0.0f;
        }

        bool is_valid() const noexcept
        {
            return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
        }

        template <typename Type>
        void copy_to_array(Type *arr) const noexcept
        {
            arr[0] = static_cast<Type>(x);
            arr[1] = static_cast<Type>(y);
            arr[2] = static_cast<Type>(z);
        }

        inline void zero() noexcept
        {
            this->x = 0.f;
            this->y = 0.f;
            this->z = 0.f;
        }

        inline void negate() noexcept
        {
            this->x = -this->x;
            this->y = -this->y;
            this->z = -this->z;
        }

        inline float distance_to(const vec3 &v) const noexcept
        {
            return (*this - v).length();
        }

        inline float distance_to_sqr(const vec3 &v) const noexcept
        {
            return (*this - v).length_3d_sqr();
        }

        inline float length_sqr() const noexcept
        {
            return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
        }
    };
}

#endif
