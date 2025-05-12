cmake_minimum_required(VERSION 3.14)
project(ascii85_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_library(ascii85 STATIC
    decoder_alg.cpp        # реализация encode / decode
    decoder_h.h            # заголовок (для IDE; можно опустить)
)
target_include_directories(ascii85 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tests
    tests_ascii85.cpp
)
target_link_libraries(tests
    ascii85
    gtest_main             # `gtest` подтягивается transitively
)

include(GoogleTest)
gtest_discover_tests(tests)
