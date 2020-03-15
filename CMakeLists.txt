cmake_minimum_required(VERSION 2.6)

project(meta2Cpp)

ADD_COMPILE_OPTIONS(-g3 -Wall -O2 -fPIC)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_BUILD_TYPE DEBUG)

INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

SET(SOURCE
    src/main.cpp
)

ADD_EXECUTABLE(codeGen ${SOURCE}
)

TARGET_LINK_LIBRARIES(codeGen
    boost_program_options
    boost_system
    boost_filesystem
)