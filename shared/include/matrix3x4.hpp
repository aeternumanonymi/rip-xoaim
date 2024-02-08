#ifndef MATRIX3X4_H
#define MATRIX3X4_H

#include "vec.hpp"
#include <numeric>

class matrix3x4_t
{
	using vec3_t = math::vec3;

public:
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;
		m_flMatVal[0][1] = m01;
		m_flMatVal[0][2] = m02;
		m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;
		m_flMatVal[1][1] = m11;
		m_flMatVal[1][2] = m12;
		m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;
		m_flMatVal[2][1] = m21;
		m_flMatVal[2][2] = m22;
		m_flMatVal[2][3] = m23;
	}
	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	inline void Init(const vec3_t &xAxis, const vec3_t &yAxis, const vec3_t &zAxis, const vec3_t &vecOrigin)
	{
		m_flMatVal[0][0] = xAxis.x;
		m_flMatVal[0][1] = yAxis.x;
		m_flMatVal[0][2] = zAxis.x;
		m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y;
		m_flMatVal[1][1] = yAxis.y;
		m_flMatVal[1][2] = zAxis.y;
		m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z;
		m_flMatVal[2][1] = yAxis.z;
		m_flMatVal[2][2] = zAxis.z;
		m_flMatVal[2][3] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t(const vec3_t &xAxis, const vec3_t &yAxis, const vec3_t &zAxis, const vec3_t &vecOrigin)
	{
		Init(xAxis, yAxis, zAxis, vecOrigin);
	}

	inline void SetOrigin(vec3_t const &p)
	{
		m_flMatVal[0][3] = p.x;
		m_flMatVal[1][3] = p.y;
		m_flMatVal[2][3] = p.z;
	}

	inline void Invalidate(void)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_flMatVal[i][j] = std::numeric_limits<float>::infinity();
				;
			}
		}
	}

	vec3_t GetXAxis() const { return at(0); }
	vec3_t GetYAxis() const { return at(1); }
	vec3_t GetZAxis() const { return at(2); }
	vec3_t GetOrigin() const { return at(3); }

	vec3_t at(int i) const { return vec3_t{m_flMatVal[0][i], m_flMatVal[1][i], m_flMatVal[2][i]}; }

	float *operator[](int i) { return m_flMatVal[i]; }
	const float *operator[](int i) const { return m_flMatVal[i]; }
	float *Base() { return &m_flMatVal[0][0]; }
	const float *Base() const { return &m_flMatVal[0][0]; }

	float m_flMatVal[3][4];
};

#endif