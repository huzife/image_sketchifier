cmake_minimum_required(VERSION 3.10)
project(image_sketchifier)

add_compile_options(-std=c++17)

find_package(OpenCV REQUIRED)

include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(sketchify
    src/image.cpp
    src/main.cpp
    src/sketchify.cpp
)

target_link_libraries(sketchify
    ${OpenCV_LIBS}
)
