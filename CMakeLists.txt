cmake_minimum_required(VERSION 3.20)
project(edge_config_manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ecm src/main.cpp)

# ---- tests ----
include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)

add_executable(ecm_tests tests/test_basic.cpp)
target_link_libraries(ecm_tests PRIVATE Catch2::Catch2WithMain)

add_test(NAME ecm_tests COMMAND ecm_tests)
