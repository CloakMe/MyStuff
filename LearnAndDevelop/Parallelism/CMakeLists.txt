set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(TBB REQUIRED)

# Collect all cpp files from the "src" folder
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Define the executable target for MultiThreading
add_executable(Parallelism ${SOURCES})
# THEN link libraries and set properties
target_link_libraries(Parallelism TBB::tbb)

# Include directory for headers
target_include_directories(Parallelism PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

