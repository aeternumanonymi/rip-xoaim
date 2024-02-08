#ifndef VMATRIX_H
#define VMATRIX_H

#include <cstring>

#include "matrix3x4.hpp"

namespace math
{
	class VMatrix
	{
		using vec3_t = math::vec3;

	public:
		VMatrix();
		VMatrix(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		// Creates a matrix where the X axis = forward
		// the Y axis = left, and the Z axis = up
		VMatrix(const vec3_t &forward, const vec3_t &left, const vec3_t &up);

		// Construct from a 3x4 matrix
		VMatrix(const matrix3x4_t &matrix3x4);

		// Set the values in the matrix.
		void Init(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		// Initialize from a 3x4
		void Init(const matrix3x4_t &matrix3x4);

		// array access
		inline float *operator[](int i)
		{
			return m[i];
		}

		inline const float *operator[](int i) const
		{
			return m[i];
		}

		// Get a pointer to m[0][0]
		inline float *Base()
		{
			return &m[0][0];
		}

		inline const float *Base() const
		{
			return &m[0][0];
		}

		void SetLeft(const vec3_t &vLeft);
		void SetUp(const vec3_t &vUp);
		void SetForward(const vec3_t &vForward);

		void GetBasisVectors(vec3_t &vForward, vec3_t &vLeft, vec3_t &vUp) const;
		void SetBasisVectors(const vec3_t &vForward, const vec3_t &vLeft, const vec3_t &vUp);

		// Get/Set the translation.
		vec3_t &GetTranslation(vec3_t &vTrans) const;
		void SetTranslation(const vec3_t &vTrans);

		void PreTranslate(const vec3_t &vTrans);
		void PostTranslate(const vec3_t &vTrans);

		matrix3x4_t &As3x4();
		const matrix3x4_t &As3x4() const;
		void CopyFrom3x4(const matrix3x4_t &m3x4);
		void Set3x4(matrix3x4_t &matrix3x4) const;

		constexpr bool operator==(const VMatrix &src) const;
		constexpr bool operator!=(const VMatrix &src) const { return !(*this == src); }

		// Access the basis vectors.
		vec3_t GetLeft() const;
		vec3_t GetUp() const;
		vec3_t GetForward() const;
		vec3_t GetTranslation() const;

		// Matrix->vector operations.
	public:
		// Multiply by a 3D vector (same as operator*).
		void V3Mul(const vec3_t &vIn, vec3_t &vOut) const;

		// Multiply by a 4D vector.
		// void  V4Mul( const Vector4D &vIn, Vector4D &vOut ) const;

		// Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
		vec3_t ApplyRotation(const vec3_t &vVec) const;

		// Multiply by a vector (divides by w, assumes input w is 1).
		vec3_t operator*(const vec3_t &vVec) const;

		// Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
		vec3_t VMul3x3(const vec3_t &vVec) const;

		// Apply the inverse (transposed) rotation (only works on pure rotation matrix)
		vec3_t VMul3x3Transpose(const vec3_t &vVec) const;

		// Multiply by the upper 3 rows.
		vec3_t VMul4x3(const vec3_t &vVec) const;

		// Apply the inverse (transposed) transformation (only works on pure rotation/translation)
		vec3_t VMul4x3Transpose(const vec3_t &vVec) const;

		// Matrix->plane operations.
		// public:
		// Transform the plane. The matrix can only contain translation and rotation.
		// void  TransformPlane( const VPlane &inPlane, VPlane &outPlane ) const;

		// Just calls TransformPlane and returns the result.
		// VPlane  operator*(const VPlane &thePlane) const;

		// Matrix->matrix operations.
	public:
		VMatrix &operator=(const VMatrix &mOther);

		// Add two matrices.
		const VMatrix &operator+=(const VMatrix &other);

		// Add/Subtract two matrices.
		VMatrix operator+(const VMatrix &other) const;
		VMatrix operator-(const VMatrix &other) const;

		// Negation.
		VMatrix operator-() const;

		// Return inverse matrix. Be careful because the results are undefined
		// if the matrix doesn't have an inverse (ie: InverseGeneral returns false).
		VMatrix operator~() const;

		// Matrix operations.
	public:
		// Set to identity.
		void Identity();
		bool IsIdentity() const;

	public:
		// The matrix.
		float m[4][4];
	};
}

using VMatrix = math::VMatrix;

inline void MatrixGetColumn(const matrix3x4_t &src, int nCol, math::vec3 &pColumn)
{
	pColumn.x = src[0][nCol];
	pColumn.y = src[1][nCol];
	pColumn.z = src[2][nCol];
}

inline void MatrixPosition(const matrix3x4_t &matrix, math::vec3 &position)
{
	MatrixGetColumn(matrix, 3, position);
}

inline VMatrix::VMatrix()
{
}

inline VMatrix::VMatrix(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	Init(
		m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33);
}

inline VMatrix::VMatrix(const matrix3x4_t &matrix3x4)
{
	Init(matrix3x4);
}

//-----------------------------------------------------------------------------
// Creates a matrix where the X axis = forward
// the Y axis = left, and the Z axis = up
//-----------------------------------------------------------------------------
inline VMatrix::VMatrix(const vec3_t &xAxis, const vec3_t &yAxis, const vec3_t &zAxis)
{
	Init(
		xAxis.x, yAxis.x, zAxis.x, 0.0f,
		xAxis.y, yAxis.y, zAxis.y, 0.0f,
		xAxis.z, yAxis.z, zAxis.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

inline void VMatrix::Init(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[0][3] = m03;

	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[1][3] = m13;

	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
	m[2][3] = m23;

	m[3][0] = m30;
	m[3][1] = m31;
	m[3][2] = m32;
	m[3][3] = m33;
}

//-----------------------------------------------------------------------------
// Initialize from a 3x4
//-----------------------------------------------------------------------------
inline void VMatrix::Init(const matrix3x4_t &matrix3x4)
{
	memcpy(m, matrix3x4.Base(), sizeof(matrix3x4_t));

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

//-----------------------------------------------------------------------------
// Vector3DMultiplyPosition treats src2 as if it's a point (adds the translation)
//-----------------------------------------------------------------------------
// NJS: src2 is passed in as a full vector rather than a reference to prevent the need
// for 2 branches and a potential copy in the body.  (ie, handling the case when the src2
// reference is the same as the dst reference ).
inline void Vector3DMultiplyPosition(const VMatrix &src1, const math::vec3 &src2, math::vec3 &dst)
{
	dst.x = src1[0][0] * src2.x + src1[0][1] * src2.y + src1[0][2] * src2.z + src1[0][3];
	dst.y = src1[1][0] * src2.x + src1[1][1] * src2.y + src1[1][2] * src2.z + src1[1][3];
	dst.z = src1[2][0] * src2.x + src1[2][1] * src2.y + src1[2][2] * src2.z + src1[2][3];
}

//-----------------------------------------------------------------------------
// Methods related to the basis vectors of the matrix
//-----------------------------------------------------------------------------

inline math::vec3 VMatrix::GetForward() const
{
	return vec3_t(m[0][0], m[1][0], m[2][0]);
}

inline math::vec3 VMatrix::GetLeft() const
{
	return vec3_t(m[0][1], m[1][1], m[2][1]);
}

inline math::vec3 VMatrix::GetUp() const
{
	return vec3_t(m[0][2], m[1][2], m[2][2]);
}

inline void VMatrix::SetForward(const vec3_t &vForward)
{
	m[0][0] = vForward.x;
	m[1][0] = vForward.y;
	m[2][0] = vForward.z;
}

inline void VMatrix::SetLeft(const vec3_t &vLeft)
{
	m[0][1] = vLeft.x;
	m[1][1] = vLeft.y;
	m[2][1] = vLeft.z;
}

inline void VMatrix::SetUp(const vec3_t &vUp)
{
	m[0][2] = vUp.x;
	m[1][2] = vUp.y;
	m[2][2] = vUp.z;
}

inline void VMatrix::GetBasisVectors(vec3_t &vForward, vec3_t &vLeft, vec3_t &vUp) const
{
	vForward = {m[0][0], m[1][0], m[2][0]};
	vLeft = {m[0][1], m[1][1], m[2][1]};
	vUp = {m[0][2], m[1][2], m[2][2]};
}

inline void VMatrix::SetBasisVectors(const vec3_t &vForward, const vec3_t &vLeft, const vec3_t &vUp)
{
	SetForward(vForward);
	SetLeft(vLeft);
	SetUp(vUp);
}

//-----------------------------------------------------------------------------
// Methods related to the translation component of the matrix
//-----------------------------------------------------------------------------

inline math::vec3 VMatrix::GetTranslation() const
{
	return vec3_t(m[0][3], m[1][3], m[2][3]);
}

inline math::vec3 &VMatrix::GetTranslation(vec3_t &vTrans) const
{
	vTrans.x = m[0][3];
	vTrans.y = m[1][3];
	vTrans.z = m[2][3];
	return vTrans;
}

inline void VMatrix::SetTranslation(const vec3_t &vTrans)
{
	m[0][3] = vTrans.x;
	m[1][3] = vTrans.y;
	m[2][3] = vTrans.z;
}

//-----------------------------------------------------------------------------
// appply translation to this matrix in the input space
//-----------------------------------------------------------------------------
inline void VMatrix::PreTranslate(const vec3_t &vTrans)
{
	vec3_t tmp;
	Vector3DMultiplyPosition(*this, vTrans, tmp);
	m[0][3] = tmp.x;
	m[1][3] = tmp.y;
	m[2][3] = tmp.z;
}

//-----------------------------------------------------------------------------
// appply translation to this matrix in the output space
//-----------------------------------------------------------------------------
inline void VMatrix::PostTranslate(const vec3_t &vTrans)
{
	m[0][3] += vTrans.x;
	m[1][3] += vTrans.y;
	m[2][3] += vTrans.z;
}

inline const matrix3x4_t &VMatrix::As3x4() const
{
	return *((const matrix3x4_t *)this);
}

inline matrix3x4_t &VMatrix::As3x4()
{
	return *((matrix3x4_t *)this);
}

inline void VMatrix::CopyFrom3x4(const matrix3x4_t &m3x4)
{
	memcpy(m, m3x4.Base(), sizeof(matrix3x4_t));
	m[3][0] = m[3][1] = m[3][2] = 0;
	m[3][3] = 1;
}

inline void VMatrix::Set3x4(matrix3x4_t &matrix3x4) const
{
	memcpy(matrix3x4.Base(), m, sizeof(matrix3x4_t));
}

//-----------------------------------------------------------------------------
// Matrix Math operations
//-----------------------------------------------------------------------------
inline const VMatrix &VMatrix::operator+=(const VMatrix &other)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] += other.m[i][j];
		}
	}

	return *this;
}

inline VMatrix VMatrix::operator+(const VMatrix &other) const
{
	VMatrix ret;
	for (int i = 0; i < 16; i++)
	{
		((float *)ret.m)[i] = ((float *)m)[i] + ((float *)other.m)[i];
	}
	return ret;
}

inline VMatrix VMatrix::operator-(const VMatrix &other) const
{
	VMatrix ret;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ret.m[i][j] = m[i][j] - other.m[i][j];
		}
	}

	return ret;
}

inline VMatrix VMatrix::operator-() const
{
	VMatrix ret;
	for (int i = 0; i < 16; i++)
	{
		((float *)ret.m)[i] = -((float *)m)[i];
	}
	return ret;
}

constexpr bool VMatrix::operator==(const VMatrix &src) const
{
	for (int i = 0; i < 16; i++)
	{
		if (((float *)m)[i] != ((float *)src.m)[i])
		{
			return false;
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
// Vector transformation
//-----------------------------------------------------------------------------

inline math::vec3 VMatrix::operator*(const math::vec3 &vVec) const
{
	vec3_t vRet;
	vRet.x = m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z + m[0][3];
	vRet.y = m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z + m[1][3];
	vRet.z = m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z + m[2][3];

	return vRet;
}

inline math::vec3 VMatrix::VMul4x3(const math::vec3 &vVec) const
{
	vec3_t vResult;
	Vector3DMultiplyPosition(*this, vVec, vResult);
	return vResult;
}

inline math::vec3 VMatrix::VMul4x3Transpose(const math::vec3 &vVec) const
{
	vec3_t tmp = vVec;
	tmp.x -= m[0][3];
	tmp.y -= m[1][3];
	tmp.z -= m[2][3];

	return vec3_t(
		m[0][0] * tmp.x + m[1][0] * tmp.y + m[2][0] * tmp.z,
		m[0][1] * tmp.x + m[1][1] * tmp.y + m[2][1] * tmp.z,
		m[0][2] * tmp.x + m[1][2] * tmp.y + m[2][2] * tmp.z);
}

inline math::vec3 VMatrix::VMul3x3(const math::vec3 &vVec) const
{
	return vec3_t(
		m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z,
		m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z,
		m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z);
}

inline math::vec3 VMatrix::VMul3x3Transpose(const math::vec3 &vVec) const
{
	return vec3_t(
		m[0][0] * vVec.x + m[1][0] * vVec.y + m[2][0] * vVec.z,
		m[0][1] * vVec.x + m[1][1] * vVec.y + m[2][1] * vVec.z,
		m[0][2] * vVec.x + m[1][2] * vVec.y + m[2][2] * vVec.z);
}

inline void VMatrix::V3Mul(const math::vec3 &vIn, math::vec3 &vOut) const
{
	float rw;

	rw = 1.0f / (m[3][0] * vIn.x + m[3][1] * vIn.y + m[3][2] * vIn.z + m[3][3]);
	vOut.x = (m[0][0] * vIn.x + m[0][1] * vIn.y + m[0][2] * vIn.z + m[0][3]) * rw;
	vOut.y = (m[1][0] * vIn.x + m[1][1] * vIn.y + m[1][2] * vIn.z + m[1][3]) * rw;
	vOut.z = (m[2][0] * vIn.x + m[2][1] * vIn.y + m[2][2] * vIn.z + m[2][3]) * rw;
}

//-----------------------------------------------------------------------------
// Other random stuff
//-----------------------------------------------------------------------------
inline void VMatrix::Identity()
{
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;
	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;
	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;
	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

inline bool VMatrix::IsIdentity() const
{
	return m[0][0] == 1.0f && m[0][1] == 0.0f && m[0][2] == 0.0f && m[0][3] == 0.0f &&
		   m[1][0] == 0.0f && m[1][1] == 1.0f && m[1][2] == 0.0f && m[1][3] == 0.0f &&
		   m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 1.0f && m[2][3] == 0.0f &&
		   m[3][0] == 0.0f && m[3][1] == 0.0f && m[3][2] == 0.0f && m[3][3] == 1.0f;
}

inline math::vec3 VMatrix::ApplyRotation(const math::vec3 &vVec) const
{
	return VMul3x3(vVec);
}

#endif
