#include "../include/file.h"
#include <typeinfo>

rstzr::File::File(std::string filename)
		: m_filename(filename), m_mode(0)
{ /*empty*/
}
/**
 * @brief Read json and save figures to canvas
 */
void rstzr::File::read(Canvas  &cv)
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
     cv.width(w);
     cv.height(h);

     m_filename = scene.at("filename");

     //Load palette

     //Load background image

     // Get all graphic objects
     auto objs = scene.at("objects");
     std::vector<std::unique_ptr<Graphic>> graphics;
     for( auto i=0u; i < objs.size(); i++)
     	graphics.push_back( invoke(objs[i]) );

     std::cout << scene.at("objects") << "\n";
     std::cout << graphics.size() << "\n";


	std::cout << graphics[0] << std::endl;

     // Return objects

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
std::unique_ptr<rstzr::Graphic> rstzr::File::invoke(json &j){
	std::string name = j.at("type");
	if(name ==  "arc"){
		Arc arc(j);
		return std::make_unique<Arc>(j);
	}
	else{
	 	std::cout << "error\n";
	 	Arc arc(j);
		return std::make_unique<Arc>(j);

	}
}