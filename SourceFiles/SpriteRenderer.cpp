#include <glad/glad.h>


#include "SpriteRenderer.h"
#include "VAO.h"
#include "VBO.h"
#include "Texture.h"

SpriteRenderer::SpriteRenderer(Shader &shader)
{
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    this->quadVAO.Delete();
}

void SpriteRenderer::DrawSprite(Texture &texture, glm::vec2 position,
    glm::vec2 size, float rotate,
    glm::vec3 color)
    {
        this->shader.Activate();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position, 0.0f));
        
        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
        model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

        model = glm::scale(model, glm::vec3(size, 1.0f));

        
        this->shader.setMat4("model", model);
        this->shader.set3Float("spriteColor", color);

        glActiveTexture(GL_TEXTURE0);
        texture.bindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
     
        this->quadVAO.Bind();
        
        glDrawArrays(GL_TRIANGLES, 0, 6);

        this->quadVAO.Unbind();
    }



void SpriteRenderer::initRenderData()
{
    // Configure VAO/VBO
    float vertices[] = {
    // pos          // tex
    0.0f, 1.0f,     0.0f, 1.0f,
    1.0f, 0.0f,     1.0f, 0.0f,
    0.0f, 0.0f,     0.0f, 0.0f, 

    0.0f, 1.0f,     0.0f, 1.0f,
    1.0f, 1.0f,     1.0f, 1.0f,
    1.0f, 0.0f,     1.0f, 0.0f
    };

    this->quadVAO.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    
    this->quadVAO.LinkAttrib(VBO1, 0, 4, GL_FLOAT, 4 * sizeof(GLfloat), (void*)0);

    this->quadVAO.Unbind();


    }
