#include <iostream>
#include <fstream>

int main()
{
	std::ofstream outputImgFile;
	outputImgFile.open("HelloWorldGraphics.ppm", std::ios_base::out | std::ios_base::binary);
	int width = 800;
	int height = 600;
	outputImgFile << "P3\n" << width << " " << height << "\n255\n";
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			float r = float(i) / float(width);
			float g = float(j) / float(height);
			float b = 0.2;

			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			outputImgFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outputImgFile.close();
    return 0;
}