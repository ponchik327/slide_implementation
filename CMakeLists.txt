cmake_minimum_required(VERSION 3.10)

project(Slide CXX)
set(CMAKE_CXX_STANDARD 17)

set(SLIDE_SRC 
    main.cpp
    object.cpp
    object.h
    slide.cpp
    slide.h
    common.h
)

add_executable(
    build_slide
    ${SLIDE_SRC}
)
