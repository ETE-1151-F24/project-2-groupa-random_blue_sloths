cmake_minimum_required(VERSION 3.31)

set(1stProject)

set(Sources
1stProject.cpp 
)

add_executable(${This} ${Sources})
target_link_libraries(1stProject PUBLIC
    gtest_main
    Example
    )

add_test(
    NAME ${This}
    COMMAND ${This}
)