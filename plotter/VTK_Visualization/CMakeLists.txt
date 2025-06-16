cmake_minimum_required(VERSION 3.10)
project(VTK_Visualization)

find_package(VTK REQUIRED COMPONENTS
  vtkCommonCore
  vtkRenderingCore
  vtkRenderingOpenGL2
  vtkInteractionStyle
)

add_executable(VTK_Visualization main.cpp)

target_link_libraries(VTK_Visualization PRIVATE ${VTK_LIBRARIES})

vtk_module_autoinit(
  TARGETS VTK_Visualization
  MODULES vtkRenderingOpenGL2 vtkInteractionStyle
)