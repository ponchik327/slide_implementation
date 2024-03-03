cmake_minimum_required(VERSION 3.10)

project(Slide CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_COMPILER "E:\\msys64\\mingw64\\bin\\g++.exe")

set(SLIDE_SRC 
    main.cpp
    object.cpp
    object.h
    slide.cpp
    slide.h
    geometry.h
)

add_executable(
    build_slide
    ${SLIDE_SRC}
)
