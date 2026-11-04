#ifndef TEXTURES_H
#define TEXTURES_H

#include<glad/glad.h>
#include<string>
#include "stb_image.h"


class Texture{

    public:
    GLuint ID;
    GLenum textureType;

    Texture();

    void bindTexture(GLenum targetType, GLenum textureUnit);
    void TextureParameters( GLenum wrapTypeS, GLenum wrapTypeT,  GLenum minFilterType, GLenum magFilterType);
    void loadTexture(const std::string &name, GLuint mipmapLevel, GLenum targetFormat, 
        GLenum sourceFormat, GLenum sourceType);

};


#endif
