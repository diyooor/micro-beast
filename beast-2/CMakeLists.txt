cmake_minimum_required(VERSION 3.25)

project(beast)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

file(GLOB_RECURSE SOURCE_FILES
  "src/*.cpp"
  "main.cpp")

add_executable(main ${SOURCE_FILES})
