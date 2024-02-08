#ifndef VEC4_H
#define VEC4_H

#include <type_traits>
#include <stdexcept>
#include <array>
#include <cmath>

namespace math
{
    class vec4
    {
    public:
        float x, y, z, w;

        vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

        vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        vec4(const vec4 &v) noexcept : x(v.x), y(v.y), z(v.z), w(v.w) {}

        float &operator[](size_t index)
        {
            if (index == 0)
                return x;
            else if (index == 1)
                return y;
            else if (index == 2)
                return z;
            else if (index == 3)
                return w;
            else
                throw std::out_of_range("Index out of range in vec4 subscript operator.");
        }

        const float &operator[](size_t index) const
        {
            if (index == 0)
                return x;
            else if (index == 1)
                return y;
            else if (index == 2)
                return z;
            else if (index == 3)
                return w;
            else
                throw std::out_of_range("Index out of range in vec4 subscript operator.");
        }

        vec4 &operator=(const vec4 &v) noexcept
        {
            x = v.x;
            y = v.y;
            z = v.z;
            w = v.w;
            return *this;
        }

        vec4 &operator+=(const vec4 &v) noexcept
        {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return *this;
        }

        vec4 &operator-=(const vec4 &v) noexcept
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return *this;
        }

        bool operator==(const vec4 &v) const noexcept
        {
            return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
        }

        bool operator!=(const vec4 &v) const noexcept
        {
            return !(*this == v);
        }

        vec4 operator+(const vec4 &v) const noexcept
        {
            return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
        }

        vec4 operator-(const vec4 &v) const noexcept
        {
            return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
        }

        vec4 &operator*=(const vec4 &v) noexcept
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            w *= v.w;
            return *this;
        }

        vec4 &operator/=(const vec4 &v) noexcept
        {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            w /= v.w;
            return *this;
        }

        vec4 operator*(const vec4 &v) const noexcept
        {
            return vec4(x * v.x, y * v.y, z * v.z, w * v.w);
        }

        vec4 operator/(const vec4 &v) const noexcept
        {
            return vec4(x / v.x, y / v.y, z / v.z, w / v.w);
        }

        vec4 &operator*=(float scalar) noexcept
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;
            return *this;
        }

        vec4 &operator/=(float scalar) noexcept
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
            return *this;
        }

        vec4 operator*(float scalar) const noexcept
        {
            return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
        }

        vec4 operator/(float scalar) const noexcept
        {
            return vec4(x / scalar, y / scalar, z / scalar, w / scalar);
        }

        vec4 &operator+=(float scalar) noexcept
        {
            x += scalar;
            y += scalar;
            z += scalar;
            w += scalar;
            return *this;
        }

        vec4 &operator-=(float scalar) noexcept
        {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            w -= scalar;
            return *this;
        }

        vec4 operator+() const noexcept
        {
            return vec4(x, y, z, w);
        }

        vec4 operator-() const noexcept
        {
            return vec4(-x, -y, -z, -w);
        }

        bool operator==(float value) const noexcept
        {
            return (x == value) && (y == value) && (z == value) && (w == value);
        }

        bool operator!=(float value) const noexcept
        {
            return (x != value) || (y != value) || (z != value) || (w != value);
        }

        float length() const noexcept
        {
            return std::sqrt(length_4d_sqr());
        }

        float length_4d_sqr() const noexcept
        {
            return x * x + y * y + z * z + w * w;
        }

        vec4 normalized() const
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
                w /= len;
            }
        }

        float dot_product(const vec4 &v) const noexcept
        {
            return x * v.x + y * v.y + z * v.z + w * v.w;
        }

        vec4 cross_product(const vec4 &v) const noexcept
        {
            return vec4(
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x,
                0.0f);
        }

        bool is_zero() const noexcept
        {
            return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f;
        }

        bool is_valid() const noexcept
        {
            return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w);
        }

        template <typename Type>
        void copy_to_array(Type *arr) const noexcept
        {
            arr[0] = static_cast<Type>(x);
            arr[1] = static_cast<Type>(y);
            arr[2] = static_cast<Type>(z);
            arr[3] = static_cast<Type>(w);
        }

        inline void zero() noexcept
        {
            this->x = 0.f;
            this->y = 0.f;
            this->z = 0.f;
            this->w = 0.f;
        }

        inline void negate() noexcept
        {
            this->x = -this->x;
            this->y = -this->y;
            this->z = -this->z;
            this->w = -this->w;
        }

        inline float distance_to(const vec4 &v) const noexcept
        {
            return (*this - v).length();
        }

        inline float distance_to_sqr(const vec4 &v) const noexcept
        {
            return (*this - v).length_4d_sqr();
        }

        inline float length_sqr() const noexcept
        {
            return (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w);
        }
    };
}

#endif
