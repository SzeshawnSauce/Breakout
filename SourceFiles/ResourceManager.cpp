#include "ResourceManager.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cerrno>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "shaderClass.h"
#include "Texture.h"

std::map<std::string, Texture> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

std::string get_file_contents(const char* filename)
{
     std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}



// Loads and generates the shader code from source files
Shader ResourceManager::LoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vertexShaderFile, fragmentShaderFile, geometryShaderFile);
    return Shaders[name];

}

// Retrieves specified shader
Shader& ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

// Loads and generates texture from source file
Texture& ResourceManager::LoadTexture(const std::string &name, const std::string &file, GLuint mipmapLevel, GLenum targetFormat, 
    GLenum sourceFormat, GLenum sourceType)
    {
        Textures[name] = loadTextureFromFile(name, file, mipmapLevel, targetFormat, sourceFormat, sourceType);
        return Textures[name];
    }

// Retrieves specified texture
Texture& ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

// Properly deallocates all loaded resources
void ResourceManager::Clear()
{
    for(auto iter : Shaders)
        glDeleteProgram(iter.second.ID); // note to self: we use iter.second because it is a map (pair) object <key, object>

    for(auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
    
}


// Loads and generates a shader from file (no geometry shader)
Shader ResourceManager::loadShaderFromFile(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile)
{   const char* vertexSource;
    const char* fragmentSource;
    const char* geometrySource;
    // Getting strings from text files and store in variables
    std::string vertexCode   = get_file_contents(vertexShaderFile);
    std::string fragmentCode = get_file_contents(fragmentShaderFile);

    // Convert and store as character arrays
    vertexSource   = vertexCode.c_str();
    fragmentSource = fragmentCode.c_str();

    if(geometryShaderFile != nullptr)
    {
        std::string geometryCode = get_file_contents(geometryShaderFile);
        geometrySource = geometryCode.c_str();
    }
    else
    {
        geometrySource = nullptr;
    }

    Shader compiledShader(vertexSource, fragmentSource, geometrySource);

    return compiledShader;

}

Texture ResourceManager::loadTextureFromFile(const std::string &name, const std::string &file, GLuint mipmapLevel, GLenum targetFormat, 
    GLenum sourceFormat, GLenum sourceType)
{
    Texture tex;
    // Load the texture data
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true); 
    unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        tex.bindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
        tex.TextureParameters(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
        // Generates the actual texture image on the bound texture object
        glTexImage2D(tex.textureType,  mipmapLevel, targetFormat, width, height, 0, sourceFormat, sourceType, data);
        // Automatically generateas the required mipmaps for currently bound texture
        glGenerateMipmap(tex.textureType);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
    else
    {
        std::cerr << "Failed to load texture: " << file << std::endl;
    }

    // Free the image memory
    stbi_image_free(data);
    return tex;
}
