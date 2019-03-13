#ifndef _file_h_
#define _file_h_

#include <string>
#include <fstream>
#include <memory> //unique_ptr, make_unique

#include "canvas.h"
#include "graphic.h"
#include "arc.h"
#include "line.h"
#include "circle.h"

#include "json.hpp"

using json = nlohmann::json;
namespace rstzr
{
/**
 * Provide the method to read and save files
 */
class File
{

  public:
    File(std::string filename);

    ~File() = default;

    /**
     * @brief Read json and save figures to canvas
     */
    std::vector<std::unique_ptr<Graphic>> read(Canvas &cv);

    void save_ppm(const rstzr::Canvas &canvas);

  private:
    std::string m_filename;

    // 0 -> read
    // 1 -> write
    int m_mode;

    /**
             * @brief Instantiate object]
             */
    std::unique_ptr<Graphic> invoke(json &j);
};
} // namespace rstzr

#endif