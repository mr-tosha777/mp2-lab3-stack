set(target test_stack)
file(GLOB srcs "*.cpp")
add_executable(${target} ${srcs})
target_link_libraries(${target} PRIVATE gtest)