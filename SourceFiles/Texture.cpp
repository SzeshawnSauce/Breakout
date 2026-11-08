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

