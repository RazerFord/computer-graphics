cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(BattleCity)

add_executable(BattleCity 
    src/main.cpp
    src/render/RenderProgram.hpp
    src/render/RenderProgram.cpp
)

add_subdirectory(external/glfw)

target_link_libraries(BattleCity glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(BattleCity OpenGL::GL)

add_subdirectory(external/glad)

target_link_libraries(BattleCity glad)
