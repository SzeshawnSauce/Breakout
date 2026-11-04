#include "SpriteRenderer.h"
#include "VAO.h"
#include "VBO.h"


    SpriteRenderer::SpriteRenderer(Shader &shader)
    {

    }


    void SpriteRenderer::DrawSprite(Texture &texture, glm::vec2 position,
        glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
        glm::vec3 color = glm::vec3(1.0f))
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

    
            texture.bindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
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

        VAO &qVAO = this->quadVAO;
        qVAO.Bind();

        VBO VBO1(vertices, sizeof(vertices));
        
        qVAO.LinkAttrib(VBO1, 0, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);

        VBO1.Unbind();
        qVAO.Unbind();


    }
