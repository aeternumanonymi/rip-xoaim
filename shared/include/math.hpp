#ifndef MATH_H
#define MATH_H

#include <cstring>

#include "vec.hpp"
#include "qangle.hpp"
#include "matrix3x4.hpp"
#include "vmatrix.hpp"

namespace math
{
	constexpr float PI = 3.14159265358979323846f;

	template <typename T>
	constexpr auto radians_to_degrees(T x) -> T
	{
		constexpr float rad = 180.0f / PI;
		return static_cast<float>(x) * rad;
	}

	template <typename T>
	constexpr auto degrees_to_radians(T x) -> T
	{
		constexpr float deg = PI / 180.0f;
		return static_cast<float>(x) * deg;
	}

	extern void matrix_build_rotation_about_axis(const math::vec3 &vAxisOfRot, float angleDegrees, matrix3x4_t &dst);
	extern void matrix_copy(const matrix3x4_t &source, matrix3x4_t &target);
	extern void matrix_multiply(matrix3x4_t &in1, const matrix3x4_t &in2);
	extern void matrix_multiply(const VMatrix &src1, const VMatrix &src2, VMatrix &dst);
	extern void matrix_angles(const matrix3x4_t &matrix, float *angles);
	extern void angle_matrix(const math::vec3 &angles, const math::vec3 &position, matrix3x4_t &matrix);
	extern void angle_matrix(const math::vec3 &angles, matrix3x4_t &matrix);

	inline void vector_transform(const math::vec3 &in, const matrix3x4_t &in2, math::vec3 *out)
	{
		out->x = in.dot_product(math::vec3(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3];
		out->y = in.dot_product(math::vec3(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3];
		out->z = in.dot_product(math::vec3(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3];
	}

	//	inline math::vec3 angle_vectors( const QAngle& angle )
	//	{
	//		return
	//		{
	//			std::cos( degrees_to_radians( angle.x ) ) * std::cos( degrees_to_radians( angle.y ) ),
	//			std::cos( degrees_to_radians( angle.x ) ) * std::sin( degrees_to_radians( angle.y ) ),
	//			-std::sin( degrees_to_radians( angle.x ) )
	//		};
	//	}

	inline void angle_vectors(const QAngle &angle, math::vec3 *forward, math::vec3 *right = nullptr, math::vec3 *up = nullptr)
	{
		const float pitch = degrees_to_radians(angle.x);
		const float yaw = degrees_to_radians(angle.y);
		const float roll = degrees_to_radians(angle.z);

		const float sp = std::sin(pitch);
		const float sy = std::sin(yaw);
		const float sr = std::sin(roll);
		const float cp = std::cos(pitch);
		const float cy = std::cos(yaw);
		const float cr = std::cos(roll);

		if (forward != nullptr)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		if (right != nullptr)
		{
			right->x = -1 * sr * sp * cy + -1 * cr * (-sy);
			right->y = -1 * sr * sp * sy + -1 * cr * cy;
			right->z = -1 * sr * cp;
		}

		if (up != nullptr)
		{
			up->x = cr * sp * cy + (-sr) * (-sy);
			up->y = cr * sp * sy + (-sr) * cy;
			up->z = cr * cp;
		}
	}

	inline QAngle vector_angles(const math::vec3 &vec)
	{
		float pitch, yaw = 0.0f;
		if (vec.x && vec.y)
		{
			pitch = radians_to_degrees(atan2f(-vec.z, vec.length()));
			pitch += pitch < 0.0f ? 360.0f : 0.0f;

			yaw = radians_to_degrees(atan2f(vec.y, vec.x));
			yaw += yaw < 0.0f ? 360.0f : 0.0f;
		}
		else
		{
			pitch = vec.z > 0.0f ? 270.0f : 90.0f;
		}

		return {pitch, yaw, 0.0f};
	}

	inline void vector_angles(const math::vec3 &forward, const math::vec3 &up, QAngle *angles)
	{
		const auto left = up.cross_product(forward).normalized();
		const float xyDist = sqrtf(forward.x * forward.x + forward.y * forward.y);

		if (xyDist > 0.001f)
		{
			angles->y = radians_to_degrees(atan2f(forward.y, forward.x));
			angles->x = radians_to_degrees(atan2f(-forward.z, xyDist));

			float up_z = (left.y * forward.x) - (left.x * forward.y);
			angles->z = radians_to_degrees(atan2f(left.z, up_z));
		}
		else
		{
			angles->y = radians_to_degrees(atan2f(-left.x, left.y));
			angles->x = radians_to_degrees(atan2f(-forward.z, xyDist));
			angles->z = 0.0f;
		}
	}

	inline float normalize_angle(float axis)
	{
		return std::isfinite(axis) ? std::remainder(axis, 360.0f) : 0.0f;
	}

	inline void clamp_angle(QAngle *angle)
	{
		angle->x = (std::max)(-89.0f, (std::min)(89.0f, normalize_angle(angle->x)));
		angle->y = normalize_angle(angle->y);
		angle->z = 0.0f;
	}

	inline QAngle clamp_angle(const QAngle &angle)
	{
		auto ang = angle;
		clamp_angle(&ang);
		return ang;
	}

	inline float angle_distance(const QAngle &start, const QAngle &end, const float distance)
	{
		auto delta = end - start;
		clamp_angle(&delta);

		float pitch = ((degrees_to_radians(fabsf(delta.x)) * distance) * 0.1905f);
		float yaw = ((degrees_to_radians(fabsf(delta.y)) * distance) * 0.1905f);

		return sqrtf(powf(pitch, 2.0f) + powf(yaw, 2.0f));
	}

	inline QAngle get_target_angles(const math::vec3 &target_pos, const math::vec3 &local_pos)
	{
		auto forward = (target_pos - local_pos);
		forward.normalize();

		return vector_angles(forward);
	}

	inline QAngle smooth_angle(const QAngle &local_angles, const QAngle &target_angles, const float speed)
	{
		const auto delta = math::clamp_angle(target_angles - local_angles);
		if (delta.is_valid())
		{
			return math::clamp_angle(local_angles + (delta * 0.01f * speed));
		}
		else
		{
			return {};
		}
	}

	inline float dot_product(const float *v1, const float *v2)
	{
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}

	inline float dot_product(const math::vec3 &v1, const math::vec3 &v2)
	{
		return dot_product(&v1.x, &v2.x);
	}

	inline float get_fov(const QAngle &viewangles, const math::vec3 &eye_pos, const math::vec3 &target_position)
	{
		const auto delta = (target_position - eye_pos).normalized();
		math::vec3 forward;
		angle_vectors(viewangles, &forward);
		return radians_to_degrees(acos(delta.dot_product(forward)));
	}

	inline void matrix_get_column(const math::vec3 &in, int column, matrix3x4_t &out)
	{
		out[0][column] = in.x;
		out[1][column] = in.y;
		out[2][column] = in.z;
	}

	inline void matrix_get_column(const matrix3x4_t &in, int column, math::vec3 *out)
	{
		out->x = in[0][column];
		out->y = in[1][column];
		out->z = in[2][column];
	}

	inline void matrix_position(const matrix3x4_t &matrix, math::vec3 *position)
	{
		matrix_get_column(matrix, 3, position);
	}

	inline void matrix_angles(const matrix3x4_t &matrix, QAngle *angles)
	{
		matrix_angles(matrix, &angles->x);
	}

	inline void matrix_angles(const matrix3x4_t &matrix, QAngle *angles, math::vec3 *position)
	{
		matrix_angles(matrix, angles);
		matrix_position(matrix, position);
	}

	inline void matrix_copy(const VMatrix &src, VMatrix &dst)
	{
		if (&src != &dst)
		{
			std::memcpy(dst.m, src.m, 16 * sizeof(float));
		}
	}

	inline void matrix_copy(const matrix3x4_t &source, matrix3x4_t &target)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				target[i][j] = source[i][j];
			}
		}
	}

	inline void vector_rotate(const float *in1, const matrix3x4_t &in2, float *out)
	{
		out[0] = dot_product(in1, in2[0]);
		out[1] = dot_product(in1, in2[1]);
		out[2] = dot_product(in1, in2[2]);
	}

	inline void vector_rotate(const math::vec3 &in1, const matrix3x4_t &in2, math::vec3 *out)
	{
		vector_rotate(&in1.x, in2, &out->x);
	}

	inline void vector_rotate(const math::vec3 &in1, const math::vec3 &in2, math::vec3 *out)
	{
		matrix3x4_t matRotate;
		angle_matrix(in2, matRotate);
		vector_rotate(in1, matRotate, out);
	}

	inline void sin_cos(float radians, float *sine, float *cosine)
	{
		*sine = std::sin(radians);
		*cosine = std::cos(radians);
	}
}

#endif