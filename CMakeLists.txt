cmake_minimum_required(VERSION 3.14)
project(ascii85_project)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Подключение GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Исходники
add_executable(decoder_alg.cpp
    test_ascii85.cpp
)

# Линковка GoogleTest
target_link_libraries(tests
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
