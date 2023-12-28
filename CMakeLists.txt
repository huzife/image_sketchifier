cmake_minimum_required(VERSION 3.10)
project(image_sketchifier)

add_compile_options(-std=c++17)

find_package(OpenCV REQUIRED)

add_executable(sketchify
    src/image.cpp
    src/main.cpp
    src/sketchify.cpp
    src/utils.cpp
)

target_include_directories(sketchify PUBLIC
    include
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(sketchify PRIVATE
    ${OpenCV_LIBS}
)
