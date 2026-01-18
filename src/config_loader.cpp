#include "config_loader.hpp"

#include <fstream>
#include <sstream>

LoadResult ConfigLoader::load_text(const std::string& path) const
{
    LoadResult r;

    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (!in)
    {
        r.ok = false;
        r.error_message = "Failed to open file: " + path;
        return r;
    }

    std::ostringstream ss;
    ss << in.rdbuf();

    r.ok = true;
    r.content = ss.str();
    return r;
};