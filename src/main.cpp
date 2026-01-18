#include "arg_parser.hpp"
#include <iostream>
#include <vector>
#include <string>


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

    std::cout << "Config file: " << *result.options.config_path << "\n";
    return 0;
    }