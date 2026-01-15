#include "arg_parser.hpp"

#include <sstream>

std::string ArgumentParser::usage() {
    std::ostringstream os;
    os << "Edge Config Manager\n"
        << "Usage:\n"
        << "  ecm --config <path>\n"
        << "  ecm --help\n\n"
        << "Options:\n"
        << "  --config <path>   Path to config file\n"
        << "  -h, --help        Show this help\n";
    return os.str();
}

ParseResult ArgumentParser::parse(const std::vector<std::string>& args) const {
    ParseResult r;

    if (args.empty()) {
        r.ok = false;
        r.exit_code = 2;
        r.error_message = "No arguments provided.";
        return r;
    }

    for (size_t i = 0; i < args.size(); ++i) {
        const auto& a = args[i];

        if (a == "--help" || a == "-h") {
            r.ok = true;
            r.exit_code = 0;
            r.options.show_help = true;
            return r;
        }

        if (a == "--config") {
            if (i + 1 >= args.size()) {
                r.ok = false;
                r.exit_code = 2;
                r.error_message = "Missing value for --config.";
                return r;
            }
            r.options.config_path = args[i + 1];
            ++i;
            continue;
        }

        r.ok = false;
        r.exit_code = 2;
        r.error_message = "Unknown argument: " + a;
        return r;
    }

    if (!r.options.config_path.has_value()) {
        r.ok = false;
        r.exit_code = 2;
        r.error_message = "Missing --config.";
        return r;
    }

    r.ok = true;
    r.exit_code = 0;
    return r;
}
