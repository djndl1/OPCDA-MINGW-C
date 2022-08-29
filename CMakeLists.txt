cmake_minimum_required(VERSION 3.12)

project(OPCDA_MINGW)

add_executable(Test
    src/Test.cc include/opccomn_i.c include/OpcEnum_i.c)   
target_include_directories(Test PRIVATE include)
target_compile_options(Test PRIVATE -DUNICODE -D_UNICODE -municode)
target_link_options(Test PRIVATE -municode)