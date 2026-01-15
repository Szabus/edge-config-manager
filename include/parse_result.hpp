#pragma once

#include <string>
#include "cli_options.hpp"

struct ParseResult {
    bool ok = false;            
    int exit_code = 2;          
    std::string error_message;  
    CliOptions options{};       
};
