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
    presenter/Presenter.cpp 
    presenter/vtk/VisualizationFactory.cpp 
    presenter/vtk/MeshVisualization.cpp 
    presenter/vtk/PressureVisualization.cpp 
    presenter/vtk/VelocityVisualization.cpp 
    DB/vtk/VTK_Database.cpp
    UI/vtk/VTK_CFDVisualizer.cpp
    configuration/json/JSONConfigParser.cpp
    configuration/json/VisualizationConfigurator.cpp
    configuration/json/KeyControlsConfigurator.cpp
    common/vtk/VTK_DBWrapper.cpp
    )


# Add project headers
set(PROJECT_INCLUDES 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/common/vtk
    ${CMAKE_CURRENT_SOURCE_DIR}/DB/vtk
    ${CMAKE_CURRENT_SOURCE_DIR}/presenter 
    ${CMAKE_CURRENT_SOURCE_DIR}/presenter/vtk
    ${CMAKE_CURRENT_SOURCE_DIR}/UI/vtk
    ${CMAKE_CURRENT_SOURCE_DIR}/external
    ${CMAKE_CURRENT_SOURCE_DIR}/configuration/json
    ${VTK_LIBRARIES}
)


target_include_directories(VTK_Visualization PRIVATE ${PROJECT_INCLUDES})

target_link_libraries(VTK_Visualization PRIVATE ${VTK_LIBRARIES} OpenGL::GLX)

# Copy configuration.json to the executable output directory after build
add_custom_command(TARGET VTK_Visualization POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/configuration.json"
        $<TARGET_FILE_DIR:VTK_Visualization>/configuration.json
)


# Mandatory for VTK 9.x module system
vtk_module_autoinit(
  TARGETS VTK_Visualization
  MODULES VTK::RenderingOpenGL2 VTK::InteractionStyle
)

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
                ${CMAKE_SOURCE_DIR}/compile_commands.json)


