cmake_minimum_required(VERSION 3.14)
project(mp2_lab3_stack)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(test)