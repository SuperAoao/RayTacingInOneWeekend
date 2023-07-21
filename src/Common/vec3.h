#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <random>


class Vec3
{
    public:
    Vec3() : e{ 0, 0, 0 }{}
    Vec3(double e1, double e2, double e3) : e{ e1, e2, e3 }{}

    double x(){ return e[0]; }
    double y(){ return e[1]; }
    double z(){ return e[2]; }

	Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }

	Vec3& operator+=(const Vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	Vec3& operator*=(const double t) 
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	Vec3& operator/=(const double t) 
	{
		return *this *= 1/t;
	}

	double length()
	{
		return std::sqrt(length_squared());
	}

	double length_squared()
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	bool near_zero() const
	{
		// Return true if the vector is close to zero in all dimensions.
		const auto s = 1e-8;
		return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
	}

	inline static Vec3 random()
	{
		static std::random_device rd;
		static std::default_random_engine generator(rd());
		static std::uniform_real_distribution<double> distribution(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
		return Vec3(distribution(generator), distribution(generator), distribution(generator));
	}

	inline static Vec3 random(double min, double max)
	{
		static std::random_device rd;
		static std::default_random_engine generator(rd());
		static std::uniform_real_distribution<double> distribution(min, max);
		return Vec3(distribution(generator), distribution(generator), distribution(generator));
	}

    public:
    double e[3];
};

// Type aliases for Vec3
using Point3 = Vec3;   // 3D point
using Color = Vec3;    // RGB color

// Vec3 Utility Functions
inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
	return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}
inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
inline Vec3 operator*(const Vec3& u, double t)
{
	return Vec3(u.e[0] * t, u.e[1] * t, u.e[2] * t);
}
inline Vec3 operator*(double t, const Vec3& u)
{
	return Vec3(t * u.e[0], t * u.e[1], t * u.e[2]);
}
inline Vec3 operator/(const Vec3& u, double t)
{
	return Vec3((1/t) * u);
}
inline double dot(const Vec3& u, const Vec3& v)
{
	return u.e[0] * v.e[0] 
		+ u.e[1] * v.e[1] 
		+ u.e[2] * v.e[2];
}
inline Vec3 cross(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
inline Vec3 unit_vector(Vec3 v)
{
	return v / v.length();
}
// 生成单位圆盘上的向量
inline Vec3 random_in_unit_disk() {
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_real_distribution<double> distribution(-1, 1);
	while (true) 
	{
		auto p = Vec3(distribution(generator), distribution(generator), 0);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}
inline Vec3 random_in_unit_sphere() {
	while (true) {
		auto p = Vec3::random(-1, 1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}
inline Vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

inline Vec3 random_in_hemisphere(const Vec3& normal) {
	Vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}

// 计算一个入射向量 v 相对于法线向量 n 的反射向量
inline Vec3 reflect(const Vec3& v, const Vec3& n) 
{
	return v - 2 * dot(v, n) * n;
}

// etai_over_etat：入射介质的折射率与出射介质的折射率之比
inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat)
{
	// 计算入射光线与法线的夹角的余弦值
	auto cos_theta = std::fmin(dot(-uv, n), 1.0);
	// 计算折射光线的垂直分量
	Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	// 计算折射光线的平行分量
	Vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
	// 返回折射光线的向量
	return r_out_perp + r_out_parallel;
}
#endif