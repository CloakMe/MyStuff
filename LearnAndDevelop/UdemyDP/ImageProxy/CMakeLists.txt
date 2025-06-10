set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect all cpp files from the "src" folder
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Define the executable target for Basic
add_executable(ImageProxy ${SOURCES})

# Include directory for headers
target_include_directories(ImageProxy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

