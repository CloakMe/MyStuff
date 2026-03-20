cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the executable target for UdemyDP
add_executable(UdemyDP main.cpp)

add_subdirectory(ImageProxy)

# Include directory for headers
target_include_directories(UdemyDP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link the ImageProxy library to executable
target_link_libraries(UdemyDP PRIVATE ImageProxy)