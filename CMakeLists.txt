cmake_minimum_required(VERSION 3.12)

project(OPCDA_MINGW)

add_executable(Test
    src/Test.cc include/opccomn_i.c include/OpcEnum_i.c)   
target_include_directories(Test PRIVATE include)
target_compile_options(Test PRIVATE -DUNICODE -D_UNICODE -municode)
target_link_options(Test PRIVATE -municode)

if(TARGET_X86_64)
    SET(LIB_PATH ${OPCDA_MINGW_SOURCE_DIR}/lib/x86_64)
else()
    SET(LIB_PATH ${OPCDA_MINGW_SOURCE_DIR}/lib/i686)
endif()
add_custom_command(TARGET Test POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${LIB_PATH}/*.dll
                        ${CMAKE_BINARY_DIR})   