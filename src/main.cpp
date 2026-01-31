#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "arg_parser.hpp"
#include "config_loader.hpp"
#include "config_parser.hpp"



static std::vector<std::string> to_args(int argc, char* argv[]) {
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) 
    {   
        args.emplace_back(argv[i]);
    }
    return args;
}

int main(int argc, char* argv[]) {
    ArgumentParser parser;
    auto args = to_args(argc, argv);
    auto result = parser.parse(args);

    if (!result.ok) {
        std::cerr << "Error: " << result.error_message << "\n\n";
        std::cerr << ArgumentParser::usage();
        return result.exit_code;
    }

    if (result.options.show_help) {
        std::cout << ArgumentParser::usage();
        return 0;
    }

    ConfigLoader loader;
    auto load_result = loader.load_text(*result.options.config_path);

    if (!load_result.ok) {
        std::cerr << "Error: " << load_result.error_message << "\n";
        return 2;
    }
    if (!is_valid_json(*load_result.content)) {
        std::cerr << "Error: config file is not valid JSON\n";
        return 2;
    }
    std::cout << "Loaded config file: "
        << result.options.config_path.value()
        << " (" << load_result.content->size()
        << " bytes)\n";

    return 0;
    }