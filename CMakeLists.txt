cmake_minimum_required(VERSION 3.26)
project(pag2)

set(CMAKE_CXX_STANDARD 17)

file(GLOB MY_FILES *.cpp)
file(GLOB GLAD_FILES GLAD/src/*.c)
file(GLOB IMGUI_FILES imgui/src/*.cpp)

add_executable(${PROJECT_NAME} ${MY_FILES} ${GLAD_FILES} ${IMGUI_FILES}..
        Renderer.cpp
        Renderer.h
        Renderer.h
        Listener.h
        Listener.h
        Shader.cpp
        Shader.h
        camara.cpp
        camara.h
)

target_include_directories(${PROJECT_NAME} PUBLIC GLAD/include imgui/include)


find_package(opengl_system)
find_package(opengl-registry)
find_package(glfw3)
find_package(glm)


target_link_libraries(${PROJECT_NAME} opengl::opengl)
target_link_libraries(${PROJECT_NAME} opengl-registry::opengl-registry)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glm::glm)