cmake_minimum_required(VERSION 3.14)

project(tlsh_example LANGUAGES C)

add_executable(tlsh_example tlsh_example.c)
target_compile_options(tlsh_example PRIVATE -Wall)

find_package(tlshc REQUIRED)

target_link_libraries(tlsh_example
        PUBLIC 
                tlshc
)
