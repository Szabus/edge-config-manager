cmake_minimum_required(VERSION 3.20)

project(edge_config_manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# (opcionális, de céges környezetben nagyon hasznos)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# =========================
# FetchContent dependencies
# =========================
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.4
)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(Catch2 nlohmann_json)

# =========================
# Core library (shared logic)
# =========================
add_library(ecm_core
    src/arg_parser.cpp
    src/config_loader.cpp
    src/config_parser.cpp
)

target_include_directories(ecm_core
    PUBLIC
        include
)

target_compile_features(ecm_core PUBLIC cxx_std_20)
if (MSVC)
    target_compile_options(ecm_core PUBLIC /std:c++20)
endif()

target_link_libraries(ecm_core
    PUBLIC
        nlohmann_json::nlohmann_json
)

# =========================
# Core executable
# =========================
add_executable(ecm
    src/main.cpp
)

target_link_libraries(ecm
    PRIVATE
        ecm_core
)

# =========================
# Testing
# =========================
include(CTest)
enable_testing()

add_executable(ecm_tests
    tests/test_basic.cpp
    tests/test_arg_parser.cpp
    tests/test_config_loader.cpp
)

target_link_libraries(ecm_tests
    PRIVATE
        Catch2::Catch2WithMain
        ecm_core
)

add_test(
    NAME ecm_tests
    COMMAND $<TARGET_FILE:ecm_tests>
)
