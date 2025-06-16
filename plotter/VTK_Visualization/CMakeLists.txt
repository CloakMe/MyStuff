cmake_minimum_required(VERSION 3.10)

project(VTK_Visualization)

find_package(VTK REQUIRED COMPONENTS
  CommonCore
  CommonDataModel
  RenderingCore
  IOLegacy          # For vtkDataSetReader, vtkStructuredGridReader, etc.
  FiltersCore       # For vtkGlyph3D
  FiltersSources    # For vtkArrowSource
  CommonDataModel   # For vtkPointData
  RenderingFreeType
  InteractionStyle
  RenderingOpenGL2
)

find_package(OpenGL REQUIRED)

target_include_directories(VTK_Visualization PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(VTK_Visualization main.cpp)

target_link_libraries(VTK_Visualization PRIVATE ${VTK_LIBRARIES} OpenGL::GLX)

# Mandatory for VTK 9.x module system
vtk_module_autoinit(
  TARGETS VTK_Visualization
  MODULES VTK::RenderingOpenGL2 VTK::InteractionStyle
)