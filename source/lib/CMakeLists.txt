cmake_minimum_required(VERSION 3.0)

set(TARGET lib)
set(SOURCES SRC_${TARGET})

project(${TARGET} VERSION 1.0 LANGUAGES CXX)

file(GLOB ${SOURCES} *.cpp)

add_library(${TARGET} ${${SOURCES}})

target_link_libraries(${TARGET} PUBLIC -lstdc++fs)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)

