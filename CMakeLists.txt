cmake_minimum_required(VERSION 3.14)
project(tables)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(tables-api)
add_subdirectory(cli)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
