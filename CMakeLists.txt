cmake_minimum_required(VERSION 3.14)

project(english-french-dictionary)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(dictionary ${SOURCES})