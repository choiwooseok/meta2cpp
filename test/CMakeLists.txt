cmake_minimum_required(VERSION 2.6)

project(tApp)

ADD_COMPILE_OPTIONS(-g3 -Wall -O2 -fPIC)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_BUILD_TYPE DEBUG)

INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

INCLUDE_DIRECTORIES(
    src/generated
)

ADD_EXECUTABLE(tapp
    src/main.cpp
    src/generated/Response.cpp
    src/generated/Role.cpp
    src/generated/User.cpp
)

TARGET_LINK_LIBRARIES(tapp
    boost_program_options
)