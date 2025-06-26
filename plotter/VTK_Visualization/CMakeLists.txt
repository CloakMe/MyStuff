cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

add_executable(VTK_Visualization
    main.cpp
    presenter/VTK_Presenter.cpp 
    presenter/VisualizationFactory.cpp 
    presenter/MeshVisualization.cpp 
    presenter/PressureVisualization.cpp 
    presenter/VelocityVisualization.cpp 
    DB/VTK_FileSeries.cpp
    UI/VTK_CFDVisualizer.cpp
    )


# Add project headers
set(PROJECT_INCLUDES 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/DB
    ${CMAKE_CURRENT_SOURCE_DIR}/DB/include
    ${CMAKE_CURRENT_SOURCE_DIR}/presenter 
    ${CMAKE_CURRENT_SOURCE_DIR}/UI 
    ${VTK_LIBRARIES}
)


target_include_directories(VTK_Visualization PRIVATE ${PROJECT_INCLUDES})

target_link_libraries(VTK_Visualization PRIVATE ${VTK_LIBRARIES} OpenGL::GLX)

# Mandatory for VTK 9.x module system
vtk_module_autoinit(
  TARGETS VTK_Visualization
  MODULES VTK::RenderingOpenGL2 VTK::InteractionStyle
)

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
                ${CMAKE_SOURCE_DIR}/compile_commands.json)


