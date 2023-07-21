#include <iostream>
#include <fstream>
#include <vec3.h>
#include <ray.h>
#include <hittable_list.h>
#include <sphere.h>
#include <camera.h>
#include <material.h>


Vec3 randomInUnitSphere()
{
	static std::random_device rd; // 解决重复调用崩溃问题
	static std::default_random_engine generator(rd());
	std::uniform_real_distribution<double> distribution(-1, 1);
	Vec3 p;
	do {
		p = Vec3(distribution(generator), distribution(generator), distribution(generator));
	} while (p.length_squared() > 1.0);
	return p;
}
Vec3 random_in_unit_sphere1()
{
	Vec3 p;
	do
	{
		p = 2.0f*Vec3(float(rand() / (RAND_MAX + 1.0)), float(rand() / (RAND_MAX + 1.0)), float(rand() / (RAND_MAX + 1.0))) - Vec3(1, 1, 1);
	} while (dot(p, p) >= 1.0);

	return p;
}
Vec3 color(const ray& r, hittable* world, int depth)
{
	hit_record rec;
	// 0.001这个参数很关键
	if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec))
	{
		ray scattered;
		Vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return Vec3(0, 0, 0);
		}
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
	int sampleCount = 100; // 每个像素再进行100次采样
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_real_distribution<float> distribution(0, 1);

	std::ofstream outputImgFile;
	outputImgFile.open("HelloWorldGraphics10.ppm", std::ios_base::out | std::ios_base::binary);
	int width = 200;
	int height = 100;
	Vec3 lower_left_corner(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);
	hittable_list* world = new hittable_list(std::make_shared<sphere>(Vec3(0, 0, -1), 0.5, std::make_shared<lambertian>(Color(0.8,0.3,0.3))));
	world->add(std::make_shared<sphere>(Vec3(0, -100.5, -1), 100, std::make_shared<lambertian>(Color(0.8,0.8,0.0))));
	world->add(std::make_shared<sphere>(Vec3(1, 0, -1), 0.5, std::make_shared<metal>(Color(0.8, 0.6, 0.2),0.3)));
	world->add(std::make_shared<sphere>(Vec3(-1, 0, -1), 0.5, std::make_shared<dielectric>(1.5)));
	outputImgFile << "P3\n" << width << " " << height << "\n255\n";
	Point3 lookFrom(-2.0, 2.0, 1.0);
	Point3 lookAt(0, 0, -1);
	double aspcetRatio = width / height;
	double lookDist = (lookAt - lookFrom).length();
	double aperture = 2.0;
	camera cam(lookFrom, lookAt, Vec3(0, 0, 1), 90, aspcetRatio,aperture,lookDist);
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			Vec3 col = Color(0,0,0);

			for (int s = 0; s < sampleCount; ++s)
			{
				float u = float(i + distribution(generator)) / float(width);
				float v = float(j + distribution(generator)) / float(height);
				
				col += color(cam.get_ray(u, v), world, 0);
			}
			col /= sampleCount;
			

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
	
			outputImgFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outputImgFile.close();
    return 0;
}