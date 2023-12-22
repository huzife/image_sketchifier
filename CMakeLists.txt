cmake_minimum_required(VERSION 3.10)
project(image_sketchifier)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
)
