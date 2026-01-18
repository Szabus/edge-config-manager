#pragma once

#include <string>
#include "load_result.hpp"

class ConfigLoader {
public:
    LoadResult load_text(const std::string& path) const;
};
