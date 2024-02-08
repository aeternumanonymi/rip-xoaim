#ifndef QANGLE_H
#define QANGLE_H

#include "vec.hpp"

class QAngle
{
public:
	float x, y, z;

	QAngle(void) = default;
	constexpr QAngle(float x, float y, float z) : x(x), y(y), z(z) {}
	QAngle(const QAngle &v) : x(v.x), y(v.y), z(v.z) {}

	void init(float x = 0.0f, float y = 0.0f, float z = 0.0f) noexcept;

	bool is_valid() const noexcept;
	float length() const noexcept;
	float length_sqr() const noexcept;

	operator math::vec3 &() noexcept
	{
		return *reinterpret_cast<math::vec3 *>(this);
	}

	operator const math::vec3() const noexcept
	{
		return *reinterpret_cast<const math::vec3 *>(this);
	}

	float operator[](int i) const noexcept;
	float &operator[](int i) noexcept;

	bool operator==(const QAngle &v) const noexcept;
	bool operator!=(const QAngle &v) const noexcept;

	// arithmetic operations
	QAngle &operator+=(const QAngle &v) noexcept;
	QAngle &operator+=(const math::vec3 &v) noexcept;
	QAngle &operator+=(const float v) noexcept;

	QAngle &operator-=(const QAngle &v) noexcept;
	QAngle &operator-=(const math::vec3 &v) noexcept;
	QAngle &operator-=(const float v) noexcept;

	QAngle &operator*=(const QAngle &v) noexcept;
	QAngle &operator*=(const math::vec3 &v) noexcept;
	QAngle &operator*=(const float v) noexcept;

	QAngle &operator/=(const QAngle &v) noexcept;
	QAngle &operator/=(const math::vec3 &v) noexcept;
	QAngle &operator/=(const float v) noexcept;

	QAngle operator+(const QAngle &v) const noexcept;
	QAngle operator+(const math::vec3 &v) const noexcept;
	QAngle operator+(const float v) const noexcept;

	QAngle operator-(const QAngle &v) const noexcept;
	QAngle operator-(const math::vec3 &v) const noexcept;
	QAngle operator-(const float v) const noexcept;

	QAngle operator*(const QAngle &v) const noexcept;
	QAngle operator*(const math::vec3 &v) const noexcept;
	QAngle operator*(const float v) const noexcept;

	QAngle operator/(const QAngle &v) const noexcept;
	QAngle operator/(const math::vec3 &v) const noexcept;
	QAngle operator/(const float v) const noexcept;

	// No assignment operators either...
	QAngle &operator=(const QAngle &src) noexcept;
	QAngle &operator=(const math::vec3 &src) noexcept;
};

inline void QAngle::init(float x, float y, float z) noexcept
{
	this->x = x;
	this->y = y;
	this->z = z;
}

inline bool QAngle::is_valid() const noexcept
{
	return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
}

inline float QAngle::length() const noexcept
{
	return std::sqrt(length_sqr());
}

inline float QAngle::length_sqr() const noexcept
{
	return (x * x) + (y * y) + (z * z);
}

inline float QAngle::operator[](int i) const noexcept
{
	return reinterpret_cast<const float *>(this)[i];
}

inline float &QAngle::operator[](int i) noexcept
{
	return reinterpret_cast<float *>(this)[i];
}

inline bool QAngle::operator==(const QAngle &v) const noexcept
{
	return (v.x == x) && (v.y == y) && (v.z == z);
}

inline bool QAngle::operator!=(const QAngle &v) const noexcept
{
	return (v.x != x) || (v.y != y) || (v.z != z);
}

inline QAngle &QAngle::operator+=(const QAngle &v) noexcept
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline QAngle &QAngle::operator+=(const math::vec3 &v) noexcept
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline QAngle &QAngle::operator+=(const float v) noexcept
{
	x += v;
	y += v;
	z += v;
	return *this;
}

inline QAngle &QAngle::operator-=(const QAngle &v) noexcept
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline QAngle &QAngle::operator-=(const math::vec3 &v) noexcept
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline QAngle &QAngle::operator-=(const float v) noexcept
{
	x -= v;
	y -= v;
	z -= v;
	return *this;
}

inline QAngle &QAngle::operator*=(const QAngle &v) noexcept
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

inline QAngle &QAngle::operator*=(const math::vec3 &v) noexcept
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

inline QAngle &QAngle::operator*=(float s) noexcept
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

inline QAngle &QAngle::operator/=(const QAngle &v) noexcept
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

inline QAngle &QAngle::operator/=(const math::vec3 &v) noexcept
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

inline QAngle &QAngle::operator/=(const float v) noexcept
{
	float oofl = 1.0f / v;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	return *this;
}

inline QAngle QAngle::operator+(const QAngle &v) const noexcept
{
	QAngle res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

inline QAngle QAngle::operator+(const math::vec3 &v) const noexcept
{
	QAngle res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

inline QAngle QAngle::operator+(const float v) const noexcept
{
	QAngle res;
	res.x = x + v;
	res.y = y + v;
	res.z = z + v;
	return res;
}

inline QAngle QAngle::operator-(const QAngle &v) const noexcept
{
	QAngle res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

inline QAngle QAngle::operator-(const math::vec3 &v) const noexcept
{
	QAngle res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

inline QAngle QAngle::operator-(const float v) const noexcept
{
	QAngle res;
	res.x = x - v;
	res.y = y - v;
	res.z = z - v;
	return res;
}

inline QAngle QAngle::operator*(const QAngle &v) const noexcept
{
	QAngle res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}

inline QAngle QAngle::operator*(const math::vec3 &v) const noexcept
{
	QAngle res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}

inline QAngle QAngle::operator*(const float v) const noexcept
{
	QAngle res;
	res.x = x * v;
	res.y = y * v;
	res.z = z * v;
	return res;
}

inline QAngle QAngle::operator/(const QAngle &v) const noexcept
{
	QAngle res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}

inline QAngle QAngle::operator/(const math::vec3 &v) const noexcept
{
	QAngle res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}

inline QAngle QAngle::operator/(const float v) const noexcept
{
	QAngle res;
	res.x = x / v;
	res.y = y / v;
	res.z = z / v;
	return res;
}

inline QAngle &QAngle::operator=(const QAngle &src) noexcept
{
	x = src.x;
	y = src.y;
	z = src.z;
	return *this;
}

inline QAngle &QAngle::operator=(const math::vec3 &src) noexcept
{
	x = src.x;
	y = src.y;
	z = src.z;
	return *this;
}

#endif
