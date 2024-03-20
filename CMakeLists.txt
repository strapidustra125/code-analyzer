# Минимальная версия CMake
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

option(TESTS_FLAG "Tests using flag" OFF)

set(PROJECT "code-analyzer")
project(${PROJECT} VERSION 2.0 LANGUAGES CXX)


# -std=c++11 - поддержка стандарта c++11
# -Wall      - выводить все варнинги
# -Wextra    - дополнительные варнинги
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")


# Точка входа
set(MAIN ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp)



######## =========================== Подключение подмодулей =========================== ########

set(SUBMODULE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/arg)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/base)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(${SUBMODULE_SOURCES})



message("-> TESTS_FLAG: ${TESTS_FLAG}")

#### ============= Сборка основного проекта ============= ####

if(${TESTS_FLAG} STREQUAL OFF)

    # Имя исполняемого файла для сборки
    set(TARGET ${PROJECT})

    # Исполняемый файл с исходниками библиотек
    add_executable( ${TARGET}
        ${MAIN}                 # main.cpp
    )

    # Директория для сборки бинарника
    set_target_properties(${TARGET} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/release
    )

    # Линковка библиотек (ПОРЯДОК ВАЖЕН!!!!!)
    target_link_libraries(${TARGET} source)

endif()



#### ============= Сборка тестов ============= ####

# Если при сборке передан флаг -DTESTS_FLAG=ON, то собирается бинарник для тестов
if(${TESTS_FLAG} STREQUAL ON)

    enable_testing()

    # Имя исполняемого файла для сборки
    set(TARGET ${PROJECT}_tests)

    # Исполняемый файл с исходниками библиотек
    add_executable( ${TARGET}
        ./test/source/test_main.cpp
    )

    # Директория для сборки бинарника
    set_target_properties(${TARGET} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/release
    )

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/source)

    # Подключение GoogleTest
    # Ставится из репо: sudo apt install libgtest-dev
    #
    # Сборка gtest:
    #       cd /usr/src/googletest/googletest
    #       sudo cmake CMakeLists.txt
    #       sudo make
    #       sudo cp *.a /usr/lib
    #
    # Сборка gmock:
    #       cd /usr/src/googletest/googlemock
    #       sudo cmake CMakeLists.txt
    #       sudo make
    #       sudo cp *.a /usr/lib
    # find_package(GTest REQUIRED)
    # target_link_libraries(${TARGET} gtest gmock_main gmock)

    # Линковка библиотек (ПОРЯДОК ВАЖЕН!!!!!)
    target_link_libraries(${TARGET} source test_source)

    add_test(NAME ${TARGET} COMMAND ${TARGET})

endif()
