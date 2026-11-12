add_executable(test_lab3_stack
    test_main.cpp
    test_poland.cpp
    test_tstack.cpp
    ../src/poland.cpp
)
target_link_libraries(test_lab3_stack PRIVATE gtest)