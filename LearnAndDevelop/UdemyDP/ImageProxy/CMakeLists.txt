cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect all cpp files from the "src" folder
file(GLOB ImageProxy_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Create library target
add_library(ImageProxy ${ImageProxy_SOURCES})

# Headers visible to consumers (UdemyDP executable)
target_include_directories(ImageProxy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

