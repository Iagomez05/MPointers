cmake_minimum_required(VERSION 3.20)
project(MPointers VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MPOINTER_ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

add_library(mpointers INTERFACE)
target_include_directories(mpointers INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(MSVC)
    target_compile_options(mpointers INTERFACE /W4 /permissive-)
else()
    target_compile_options(mpointers INTERFACE -Wall -Wextra -Wpedantic)
endif()

if(MPOINTER_ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(mpointers INTERFACE -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(mpointers INTERFACE -fsanitize=address,undefined)
endif()

add_executable(mpointers_demo src/main.cpp)
target_link_libraries(mpointers_demo PRIVATE mpointers)

include(CTest)
if(BUILD_TESTING)
    add_executable(mpointers_tests tests/MPointerTests.cpp)
    target_link_libraries(mpointers_tests PRIVATE mpointers)
    add_test(NAME mpointers_tests COMMAND mpointers_tests)
endif()
