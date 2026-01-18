#include <catch2/catch_test_macros.hpp>
#include "config_loader.hpp"

#include <fstream>

TEST_CASE("ConfigLoader reads an existing file") {
    
    const std::string path = "test_config_tmp.txt";
    {
        std::ofstream out(path, std::ios::out | std::ios::binary);
        REQUIRE(out.good());
        out << "hello\nworld";
    }

    // Act
    ConfigLoader loader;
    auto r = loader.load_text(path);

    // Assert
    REQUIRE(r.ok);
    REQUIRE(r.content.has_value());
    REQUIRE(*r.content == "hello\nworld");

    // Cleanup
    std::remove(path.c_str());
}

TEST_CASE("ConfigLoader returns error for missing file") {
    ConfigLoader loader;
    auto r = loader.load_text("this_file_should_not_exist_12345.txt");

    REQUIRE_FALSE(r.ok);
    REQUIRE_FALSE(r.error_message.empty());
    REQUIRE_FALSE(r.content.has_value());
}
