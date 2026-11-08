#ifndef RESOURCE_MANAGE_H
#define RESOURCE_MANAGE_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "Texture.h"
#include "shaderClass.h"



std::string get_file_contents(const char* filename);

class ResourceManager
{
    public:
        // Resource Containers
        static std::map<std::string, Shader>    Shaders;
        static std::map<std::string, Texture>   Textures;

        // Loads and generates the shader code from source files
        static Shader LoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile, std::string name);

        // Retrieves specified shader
        static Shader& GetShader(std::string name);

        // Loads and generates texture from source file
        static Texture& LoadTexture(Texture& tex, const std::string &name, const std::string &file, GLuint mipmapLevel, GLenum targetFormat, 
                GLenum sourceFormat, GLenum sourceType);

        // Retrieves specified texture
        static Texture& GetTexture(std::string name);

        // Properly deallocates all loaded resources
        static void Clear();

    private:
        // Private constructor since we don't want an actual ResourceManager Object
        // Memebers and functions should be static and public
        ResourceManager(){}

        // Loads and generates a shader from file (no geometry shader)
        static Shader loadShaderFromFile(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile);

        static Texture& loadTextureFromFile(Texture& tex, const std::string &file, GLuint mipmapLevel, GLenum targetFormat, 
                GLenum sourceFormat, GLenum sourceType);



};


#endif
