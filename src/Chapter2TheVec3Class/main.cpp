#include <iostream>
#include <fstream>
#include <vec3.h>

Vec3 color(const ray& r)
{
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t)*vec3(1.0f, 1.0f, 1.0f) + t*vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
	std::ofstream outputImgFile;
	outputImgFile.open("HelloWorldGraphics2.ppm", std::ios_base::out | std::ios_base::binary);
	int width = 800;
	int height = 600;
	outputImgFile << "P3\n" << width << " " << height << "\n255\n";
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			Vec3 vec(float(i) / float(width), float(j) / float(height), 0.2);
			int ir = int(255.99 * vec.x());
			int ig = int(255.99 * vec.y());
			int ib = int(255.99 * vec.z());
			outputImgFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outputImgFile.close();
    return 0;
}