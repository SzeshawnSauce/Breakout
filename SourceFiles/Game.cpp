#include "Game.h"
#include "SpriteRenderer.h"
#include "shaderClass.h"
#include "Texture.h"
#include "ResourceManager.h"



Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}


Game::~Game()
{
    delete Renderer;
}


void Game::Init()
{
    //Load Shaders
    ResourceManager::LoadShader("/Users/shawnlee/Desktop/ Comp_Graphics/Breakout/Resources/Shaders/default.vert", "/Users/shawnlee/Desktop/ Comp_Graphics/Breakout/Resources/Shaders/default.frag", nullptr, "ShaderProgram");
    

    //Configure Shaders

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
                        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("ShaderProgram").Activate();
    ResourceManager::GetShader("ShaderProgram").setInt("image", 0);
    ResourceManager::GetShader("ShaderProgram").setMat4("projection", projection);

    Renderer = new SpriteRenderer(ResourceManager::GetShader("ShaderProgram"));
    
}


void Game::ProcessInput(float dt)
{

}

void Game::Update(float dt)
{

}

void Game::Render()
{
    Texture lulu;
    lulu.bindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
    lulu.TextureParameters(GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR);
    lulu.loadTexture("/Users/shawnlee/Desktop/ Comp_Graphics/Breakout/Resources/TextureSource/awesomeface.png", 0, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
    Renderer->DrawSprite(lulu, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
