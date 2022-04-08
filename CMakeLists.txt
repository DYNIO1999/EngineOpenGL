cmake_minimum_required(VERSION 3.9)
project(DEngine)
set(CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set (CMAKE_VERBOSE_MAKEFILE 0) # 1 should be used for debugging
set (CMAKE_SUPPRESS_REGENERATION TRUE) # Suppresses ZERO_CHECK


option (GLFW_INSTALL OFF)
option (GLFW_BUILD_DOCS OFF)
option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)
add_subdirectory (vendor/glfw)

include_directories (src/
                     vendor/glad/include/
                     vendor/glfw/include/
                     vendor/glm/include/glm
                     vendor/stb/
                     vendor/imgui/
                     vendor/imgui/backends
                     vendor/spdlog/include
                     )
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/vendor/imgui)

file (GLOB          IMGUI_SOURCES 
                    ${IMGUI_DIR}/imgui.cpp 
                    ${IMGUI_DIR}/imgui_draw.cpp 
                    ${IMGUI_DIR}/imgui_demo.cpp 
                    ${IMGUI_DIR}/imgui_tables.cpp 
                    ${IMGUI_DIR}/imgui_widgets.cpp
                    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
                    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)

file (GLOB         STB_SOURCES vendor/stb/stb_image.cpp)
file (GLOB         GLAD_SOURCES vendor/glad/src/glad.c)
file (GLOB_RECURSE PROJECT_HEADERS src/*.hpp
                                   src/*.h)
file (GLOB_RECURSE PROJECT_SOURCES src/*.cpp
                                   src/*.cxx
                                   src/*.cc
                                   src/*.c)

file (GLOB         PROJECT_CONFIGS CMakeLists.txt)
add_definitions (-DGLFW_INCLUDE_NONE
                 -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                                 ${PROJECT_CONFIGS}
                                ${GLAD_SOURCES} ${IMGUI_SOURCES} ${STB_SOURCES})
target_link_libraries (${PROJECT_NAME}
                       glfw
                       ${GLFW_LIBRARIES}
                       ${GLAD_LIBRARIES})

set_target_properties (${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})