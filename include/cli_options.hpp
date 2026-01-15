#pragma once

#include <optional>
#include <string>

struct CliOptions {
    bool show_help = false;
    std::optional<std::string> config_path;
};