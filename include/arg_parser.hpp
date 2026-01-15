#pragma once

#include <string>
#include <vector>
#include "parse_result.hpp"

class ArgumentParser {
public:
    ParseResult parse(const std::vector<std::string>& args) const;
    static std::string usage();
};
