#pragma once

#include <optional>
#include <string>

struct LoadResult {
    bool ok = false;
    std::string error_message;
    std::optional<std::string> content;
};
