# Collect all cpp files from the "src" folder
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Define the executable target for Basic
add_executable(Basic ${SOURCES})

# Include directory for headers
target_include_directories(Basic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

