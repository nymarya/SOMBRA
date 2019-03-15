#include "../include/file.h"
#include <typeinfo>

rstzr::File::File(std::string filename)
	: m_filename(filename), m_mode(0)
{ /*empty*/
}
/**
 * @brief Read json and save figures to canvas
 */
std::vector<std::unique_ptr<rstzr::Graphic>> rstzr::File::read(Canvas &cv)
{
	// read a JSON file
	std::ifstream i(m_filename);
	json j;
	i >> j;

	// Get scene
	auto scene = j.at("scene");

	//Get canvas' data
	auto h = scene.at("height");
	auto w = scene.at("width");
	Canvas copy(w, h);
	cv = copy;

	m_filename = scene.at("filename");

	//Load palette

	//Load background image

	// Get all graphic objects
	auto objs = scene.at("objects");
	std::vector<std::unique_ptr<Graphic>> graphics;
	for (auto i = 0u; i < objs.size(); i++)
		graphics.push_back(invoke(objs[i]));

	// Return objects
	return graphics;
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

/**
 * @brief Instantiate object
 */
std::unique_ptr<rstzr::Graphic> rstzr::File::invoke(json &j)
{

	std::string name = j.at("type");
	std::cout << name << "\n";

	std::unique_ptr<rstzr::Graphic> graphic;

	if (name == "arc")
	{
		return std::make_unique<Arc>(j);
	}
	else if (name == "circle")
	{
		return std::make_unique<Circle>(j);
	}
	else if (name == "line")
	{
		return std::make_unique<Line>(j);
	}
	else if (name == "polygon")
	{
		return std::make_unique<Polygon>(j);
	}
	else if (name == "group")
	{
		std::vector<std::unique_ptr<rstzr::Graphic>> shapes;
		auto graphics = j.at("shapes");
		std::cout << j << std::endl;
		for (auto i = 0u; i < graphics.size(); i++)
			shapes.push_back( invoke( graphics[i] ) );

		return std::make_unique<GraphicComposite>(j, shapes);
	}
	else
	{
		throw std::invalid_argument("Invalid syntax. Type not found: " + name);
	}

	//TODO: Check wheter stroke and background color are
	//in the json. If not, set the canvas' info
	//If fill=None, set the method
}