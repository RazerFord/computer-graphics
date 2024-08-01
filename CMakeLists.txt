cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(BattleCity)

add_executable(BattleCity 
    src/main.cpp
    src/render/ShaderProgram.hpp
    src/render/ShaderProgram.cpp
    src/render/Texture2D.hpp
    src/render/Texture2D.cpp
    src/resources/ResourceManager.hpp
    src/resources/ResourceManager.cpp
    src/resources/stb_image.h
)

add_subdirectory(external/glfw)

target_link_libraries(BattleCity glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(BattleCity OpenGL::GL)

add_subdirectory(external/glad)

target_link_libraries(BattleCity glad)

set_target_properties(BattleCity PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_custom_command(TARGET BattleCity POST_BUILD COMMAND ${CMAKE_COMMAND} 
    -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:BattleCity>
)