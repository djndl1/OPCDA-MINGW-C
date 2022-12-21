cmake_minimum_required(VERSION 3.12)

project(OPCDA_MINGW_C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_definitions(-DUNICODE -D_UNICODE -DSTC_HEADER)
include_directories(${OPCDA_MINGW_C_SOURCE_DIR}/lib/STC-3.8/include)

if(TARGET_X86_64)
    SET(LIB_PATH ${OPCDA_MINGW_C_SOURCE_DIR}/lib/x86_64)
else()
    SET(LIB_PATH ${OPCDA_MINGW_C_SOURCE_DIR}/lib/i686)
endif()

add_library(copcda SHARED
            src/utf.c
            src/opc_locale.c
            src/stc_instantiation.c)
target_compile_definitions(copcda PRIVATE)
target_include_directories(copcda BEFORE
                            PRIVATE ${OPCDA_MINGW_C_SOURCE_DIR}/include)

add_custom_command(TARGET copcda POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${LIB_PATH}/*.dll
                        ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()
add_executable(Test2
    test/Test2.cc include/opccomn_i.c include/OpcEnum_i.c)
target_include_directories(Test2 PRIVATE ${OPCDA_MINGW_C_SOURCE_DIR}/include)
include(GoogleTest)
target_compile_options(Test2 PRIVATE -DCINTERFACE -DCOBJMACROS)
target_link_options(Test2 PRIVATE)
target_link_libraries(Test2 GTest::gtest_main)

add_test(NAME Test2 COMMAND Test2)

add_executable(utf_test test/utf_test.cc)
target_include_directories(utf_test PRIVATE ${OPCDA_MINGW_C_SOURCE_DIR}/include)
include(GoogleTest)
target_compile_definitions(utf_test PRIVATE)
target_link_options(utf_test PRIVATE)
target_link_libraries(utf_test GTest::gtest_main copcda)