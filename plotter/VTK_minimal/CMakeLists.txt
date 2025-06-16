# CMakeList.txt : CMake project for VTK_Visualization, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

project(MinimalVTKExample)

set(VTK_DIR "D:/workspaces/vtk/VTK/Build/lib/cmake/vtk-9.5")

find_package(VTK REQUIRED COMPONENTS
  CommonCore
  CommonDataModel
  FiltersCore
  RenderingCore
  InteractionStyle
  RenderingOpenGL2
)



find_package(OpenGL REQUIRED)

add_executable(MinimalVTKExample main.cpp)



#target_link_libraries(MinimalVTKExample PRIVATE ${VTK_LIBRARIES})
target_link_libraries(MinimalVTKExample PRIVATE 
  VTK::CommonCore
  VTK::CommonDataModel
  VTK::FiltersCore
  VTK::RenderingCore
  VTK::InteractionStyle
  VTK::RenderingOpenGL2
  # add other required VTK targets here
)

# Mandatory for VTK 9.x module system
vtk_module_autoinit(
  TARGETS MinimalVTKExample
  MODULES VTK::RenderingOpenGL2 VTK::InteractionStyle
)

#if (WIN32 AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
#  add_custom_command(TARGET MinimalVTKExample POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy 
#      $<TARGET_RUNTIME_DLLS:MinimalVTKExample>  # List of DLLs
#      $<TARGET_FILE_DIR:MinimalVTKExample>       # Destination directory
#    COMMAND_EXPAND_LISTS  # Split semicolon-separated list into individual args
#  )
#endif()
