#include <catch2/catch_test_macros.hpp>
#include "arg_parser.hpp"

TEST_CASE("help returns ok=true, exit_code=0, show_help=true")
{ 
	ArgumentParser parser;
	auto result = parser.parse({ "--help" });

	REQUIRE(result.ok);
	REQUIRE(result.exit_code == 0);
	REQUIRE(result.options.show_help);
}

TEST_CASE("missing --config value errors") {
    ArgumentParser p;
    auto r = p.parse({ "--config" });

    REQUIRE_FALSE(r.ok);
    REQUIRE(r.exit_code == 2);
    REQUIRE_FALSE(r.error_message.empty());
}

TEST_CASE("config parses path") {
    ArgumentParser p;
    auto r = p.parse({ "--config", "config.json" });

    REQUIRE(r.ok);
    REQUIRE(r.exit_code == 0);
    REQUIRE(r.options.config_path.has_value());
    REQUIRE(*r.options.config_path == "config.json");
}