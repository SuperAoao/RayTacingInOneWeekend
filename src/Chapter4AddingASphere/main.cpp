#include <iostream>
#include <fstream>
#include <vec3.h>
#include <ray.h>


bool hit_sphere(const Vec3& center, float radius, const ray& r)
{
	Vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0f * dot(oc, r.direction());
	float c = dot(oc, oc) - radius* radius;
	float discriminant = b*b - 4 * a*c;
	return (discriminant > 0);
}


Vec3 color(const ray& r)
{
	if (hit_sphere(Vec3(0,0,-1),0.5,r))
	{
		return Vec3(1.0, 0.0, 0.0);
	}
	else
	{
		Vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
	}
}
int main()
{
	std::ofstream outputImgFile;
	outputImgFile.open("HelloWorldGraphics4.ppm", std::ios_base::out | std::ios_base::binary);
	int width = 200;
	int height = 100;
	Vec3 lower_left_corner(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);
	outputImgFile << "P3\n" << width << " " << height << "\n255\n";
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			float u = float(i) / float(width);
			float v = float(j) / float(height);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);

			Vec3 col = color(r);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
	
			outputImgFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outputImgFile.close();
    return 0;
}