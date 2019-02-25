#include "../include/file.h"

rstzr::File::File(std::string filename)
:filename(filename)
,mode(0)
{/*empty*/}
            
void rstzr::File::read(){
    
}
            
void rstzr::File::save_ppm( const rast::Canvas &canvas){
    
    component_t * image = canvas.pixels();

	std::ofstream file;
 	
 	std::string extension = ".ppm";
 	std::string path = this->filename + extension;
    file.open (path);
    file << "P3" << "\n";
  	file << canvas.width() << " " 
  		   << canvas.height() << "\n";
  	file << 255 << "\n";

  	for (unsigned int x = 0; x < canvas.width(); x++)
  	{
  	    for (unsigned int y=0; y < canvas.height() ; y++){
  		    for (int z=0; z < 3; z++)
  			   file << static_cast<unsigned>( image[ canvas.height() *canvas.width()*z+ canvas.width()*y +x] ) << " ";
  	    }
  		file << "\n";
  	}

    file.close();
}
            