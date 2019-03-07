#include "../include/file.h"

rstzr::File::File(std::string filename)
		: m_filename(filename), m_mode(0)
{ /*empty*/
}

void rstzr::File::read()
{
}

void rstzr::File::save_ppm(const rstzr::Canvas &canvas)
{

	component_t *image = canvas.pixels();
	size_t width = canvas.width();
	size_t height = canvas.height();

	std::ofstream file;

	std::string folder = "gallery/";
	std::string extension = ".ppm";
	std::string path = folder + this->m_filename + extension;
	file.open(path);
	file << "P3"
			 << "\n";
	file << width << " "
			 << height << "\n";
	file << 255 << "\n";

	for (unsigned int x = 0; x < width; x++)
	{
		for (unsigned int y = 0; y < height; y++)
		{
			for (int z = 0; z < 3; z++)
			{
				auto index = height * width * z + width * y + x;
				file << static_cast<unsigned>(image[index]) << " ";
			}
		}
		file << "\n";
	}

	file.close();
}
