cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(BattleCity)

add_executable(BattleCity 
    src/main.cpp
    src/render/ShaderProgram.hpp
    src/render/ShaderProgram.cpp
    src/render/IndexBuffer.hpp
    src/render/IndexBuffer.cpp
    src/render/Render.hpp
    src/render/Render.cpp
    src/render/Texture2D.hpp
    src/render/Texture2D.cpp
    src/render/Sprite.hpp
    src/render/Sprite.cpp
    src/render/SpriteAnimator.hpp
    src/render/SpriteAnimator.cpp    
    src/render/VertexArray.hpp
    src/render/VertexArray.cpp
    src/render/VertexBuffer.hpp
    src/render/VertexBuffer.cpp
    src/render/VertexBufferLayout.hpp
    src/render/VertexBufferLayout.cpp
    src/resources/ResourceManager.hpp
    src/resources/ResourceManager.cpp
    src/resources/stb_image.h
    src/game/Game.hpp
    src/game/Game.cpp
    src/game/Level.hpp
    src/game/Level.cpp
    src/game/gameobjects/Border.hpp
    src/game/gameobjects/Border.cpp
    src/game/gameobjects/ConcreteWall.hpp
    src/game/gameobjects/ConcreteWall.cpp
    src/game/gameobjects/Eagle.hpp
    src/game/gameobjects/Eagle.cpp
    src/game/gameobjects/Ice.hpp
    src/game/gameobjects/Ice.cpp
    src/game/gameobjects/BrickWall.hpp
    src/game/gameobjects/BrickWall.cpp
    src/game/gameobjects/Bullet.hpp
    src/game/gameobjects/Bullet.cpp
    src/game/gameobjects/IGameObject.hpp
    src/game/gameobjects/IGameObject.cpp
    src/game/gameobjects/Tank.hpp
    src/game/gameobjects/Tank.cpp
    src/game/gameobjects/Trees.hpp
    src/game/gameobjects/Trees.cpp
    src/game/gameobjects/Water.hpp
    src/game/gameobjects/Water.cpp
    src/utils/Timer.hpp
    src/utils/Timer.cpp
    src/physics/PhysicsEngine.hpp
    src/physics/PhysicsEngine.cpp
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

include_directories(external/glm)
include_directories(external/rapidjson/include)