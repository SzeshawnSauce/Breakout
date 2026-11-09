cmake_minimum_required(VERSION 3.16)

project(Breakout)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMAKE_SOURCE_DIR is the directory that CMakeLists.txt is in
# This setting generates the executable in the given directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(Breakout 
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/Breakout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/ResourceManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/glad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/shaderClass.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/VAO.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/VBO.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/EBO.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/stb_image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/SpriteRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/GameLevel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles/GameObject.cpp
    
    
)

target_include_directories(Breakout PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/glfw-3.5.1/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/glm
)

target_link_libraries(Breakout PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/glfw-3.5.1/build/src/libglfw3.a
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework QuartzCore"
)
