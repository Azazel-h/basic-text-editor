cmake_minimum_required(VERSION 3.19...3.28)
project(basic-text-editor)
set(CMAKE_CXX_STANDARD 17)

set(GLFW_DIR "${CMAKE_SOURCE_DIR}/external/glfw")
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
add_subdirectory("${GLFW_DIR}")
include_directories("${GLFW_DIR}/include")

set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/external/imgui")
include_directories(${IMGUI_DIR} "${IMGUI_DIR}/backends")

find_package(Vulkan REQUIRED)

set(LIBRARIES "glfw;Vulkan::Vulkan")

include_directories("${CMAKE_SOURCE_DIR}/include")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(basic-text-editor
        ${SRC_FILES}
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
)
target_link_libraries(basic-text-editor ${LIBRARIES})

