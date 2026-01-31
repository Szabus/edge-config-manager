#include "config_parser.hpp"

#include <nlohmann/json.hpp>

bool is_valid_json(const std::string& text) {
    try {
        auto j = nlohmann::json::parse(text);
        (void)j;
        return true;
    }
    catch (...) {
        return false;
    }
}
