#ifndef VEC2_H
#define VEC2_H

#include <type_traits>
#include <stdexcept>
#include <array>
#include <cmath>

namespace math
{
    class vec2
    {
    public:
        float x, y;

        vec2() : x(0.0f), y(0.0f) {}

        vec2(float x, float y) : x(x), y(y) {}

        vec2(const vec2 &v) noexcept : x(v.x), y(v.y) {}

        float &operator[](size_t index)
        {
            if (index == 0)
                return x;
            else if (index == 1)
                return y;
            else
                throw std::out_of_range("Index out of range in vec2 subscript operator.");
        }

        const float &operator[](size_t index) const
        {
            if (index == 0)
                return x;
            else if (index == 1)
                return y;
            else
                throw std::out_of_range("Index out of range in vec2 subscript operator.");
        }

        vec2 &operator=(const vec2 &v) noexcept
        {
            x = v.x;
            y = v.y;
            return *this;
        }

        vec2 &operator+=(const vec2 &v) noexcept
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        vec2 &operator-=(const vec2 &v) noexcept
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        bool operator==(const vec2 &v) const noexcept
        {
            return (x == v.x) && (y == v.y);
        }

        bool operator!=(const vec2 &v) const noexcept
        {
            return !(*this == v);
        }

        vec2 operator+(const vec2 &v) const noexcept
        {
            return vec2(x + v.x, y + v.y);
        }

        vec2 operator-(const vec2 &v) const noexcept
        {
            return vec2(x - v.x, y - v.y);
        }

        vec2 &operator*=(const vec2 &v) noexcept
        {
            x *= v.x;
            y *= v.y;
            return *this;
        }

        vec2 &operator/=(const vec2 &v) noexcept
        {
            x /= v.x;
            y /= v.y;
            return *this;
        }

        vec2 operator*(const vec2 &v) const noexcept
        {
            return vec2(x * v.x, y * v.y);
        }

        vec2 &operator*=(float scalar) noexcept
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        vec2 &operator/=(float scalar) noexcept
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        vec2 operator*(float scalar) const noexcept
        {
            return vec2(x * scalar, y * scalar);
        }

        vec2 operator/(float scalar) const noexcept
        {
            return vec2(x / scalar, y / scalar);
        }

        vec2 &operator+=(float scalar) noexcept
        {
            x += scalar;
            y += scalar;
            return *this;
        }

        vec2 &operator-=(float scalar) noexcept
        {
            x -= scalar;
            y -= scalar;
            return *this;
        }

        vec2 operator+() const noexcept
        {
            return vec2(x, y);
        }

        vec2 operator-() const noexcept
        {
            return vec2(-x, -y);
        }

        bool operator==(float value) const noexcept
        {
            return (x == value) && (y == value);
        }

        bool operator!=(float value) const noexcept
        {
            return (x != value) && (y != value);
        }

        float length() const noexcept
        {
            return std::sqrt(length_2d_sqr());
        }

        float length_2d_sqr() const noexcept
        {
            return x * x + y * y;
        }

        vec2 normalized() const
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
            }
        }

        float dot_product(const vec2 &v) const noexcept
        {
            return x * v.x + y * v.y;
        }

        float cross_product(const vec2 &v) const noexcept
        {
            return x * v.y - y * v.x;
        }

        bool is_zero() const noexcept
        {
            return x == 0.0f && y == 0.0f;
        }

        bool is_valid() const noexcept
        {
            return std::isfinite(x) && std::isfinite(y);
        }

        template <typename Type>
        void copy_to_array(Type *arr) const noexcept
        {
            arr[0] = static_cast<Type>(x);
            arr[1] = static_cast<Type>(y);
        }

        inline void zero() noexcept
        {
            this->x = 0.f;
            this->y = 0.f;
        }

        inline void negate() noexcept
        {
            this->x = -this->x;
            this->y = -this->y;
        }

        inline float distance_to(const vec2 &v) const noexcept
        {
            return (*this - v).length();
        }

        inline float distance_to_sqr(const vec2 &v) const noexcept
        {
            return (*this - v).length_sqr();
        }

        inline float length_sqr() const noexcept
        {
            return (this->x * this->x) + (this->y * this->y);
        }
    };
}

#endif
