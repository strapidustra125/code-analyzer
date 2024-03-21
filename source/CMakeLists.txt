cmake_minimum_required(VERSION 3.0)

set(TARGET source)
set(SOURCES SRC_${TARGET})

project(${TARGET} VERSION 1.0 LANGUAGES CXX)

# Модуль lib
set(DIR_lib ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(${DIR_lib})

# Модуль arg
set(DIR_arg ${CMAKE_CURRENT_SOURCE_DIR}/arg)
add_subdirectory(${DIR_arg})

# Модуль base
set(DIR_base ${CMAKE_CURRENT_SOURCE_DIR}/base)
add_subdirectory(${DIR_base})


add_library(${TARGET} INTERFACE)

target_link_libraries(${TARGET} INTERFACE base arg lib )

