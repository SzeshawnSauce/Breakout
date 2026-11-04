#ifndef SPRITE_RENDER_H
#define SPRITE_RENDER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shaderClass.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"

class SpriteRenderer
{
    public:

        // Constructor/Destructor
        SpriteRenderer(Shader &shader);
        ~SpriteRenderer();

        // Draws the actual sprite using OpenGL
        void DrawSprite(Texture &texture, glm::vec2 position,
            glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
            glm::vec3 color = glm::vec3(1.0f));

    private:
        Shader          shader;
        VAO             quadVAO;

        void initRenderData();
};



#endif
