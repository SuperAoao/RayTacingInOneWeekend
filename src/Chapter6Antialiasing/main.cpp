#include <iostream>
#include <fstream>
#include <vec3.h>
#include <ray.h>
#include <hittable_list.h>
#include <sphere.h>
#include <camera.h>

Vec3 color(const ray& r, hittable* world)
{
	hit_record rec;
	if (world->hit(r, 0, std::numeric_limits<float>::max(), rec))
	{
		return 0.5 * Vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
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
	outputImgFile.open("HelloWorldGraphics6.ppm", std::ios_base::out | std::ios_base::binary);
	int width = 200;
	int height = 100;
	Vec3 lower_left_corner(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);
	hittable_list* world = new hittable_list(std::make_shared<sphere>(Vec3(0, 0, -1), 0.5, nullptr));
	world->add(std::make_shared<sphere>(Vec3(0, -100.5, -1), 100, nullptr));
	outputImgFile << "P3\n" << width << " " << height << "\n255\n";
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			Vec3 col = Color(0,0,0);

			for (int s = 0; s < sampleCount; ++s)
			{
				float u = float(i + distribution(generator)) / float(width);
				float v = float(j + distribution(generator)) / float(height);
				ray r(origin, lower_left_corner + u * horizontal + v * vertical);
				col += color(r, world);
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