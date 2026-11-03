#include <iostream>
#include "Texture.h"


Texture::Texture(){
    glGenTextures(1, &ID);
}

void Texture::bindTexture(GLenum targetType, GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(targetType, ID);
    textureType = targetType;
}

void Texture::TextureParameters(GLenum wrapTypeS, GLenum wrapTypeT, GLenum minFilterType, GLenum magFilterType)
{
    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, wrapTypeS);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, wrapTypeT);
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, minFilterType);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, magFilterType);

}

void Texture::loadTexture(const std::string &name, GLuint mipmapLevel, GLenum targetFormat, 
    GLenum sourceFormat, GLenum sourceType)
{
    // Load the texture data
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true); 
    unsigned char *data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // Generates the actual texture image on the bound texture object
        glTexImage2D(textureType,  mipmapLevel, targetFormat, width, height, 0, sourceFormat, sourceType, data);
        // Automatically generateas the required mipmaps for currently bound texture
        glGenerateMipmap(textureType);
    }
    else
    {
        std::cerr << "Failed to load texture: " << name << std::endl;
    }
    // Free the image memory
    stbi_image_free(data);
}
