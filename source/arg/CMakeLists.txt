cmake_minimum_required(VERSION 3.0)

set(TARGET arg)
set(SOURCES SRC_${TARGET})

project(${TARGET} VERSION 1.0 LANGUAGES CXX)

file(GLOB ${SOURCES} *.cpp)

add_library(${TARGET} ${${SOURCES}})
