#include "Game.h"
#include "SpriteRenderer.h"
#include "Texture.h"




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
    shader = Shader("/Users/shawnlee/Desktop/ Comp_Graphics/Breakout/Resources/Shaders/default.vert", "/Users/shawnlee/Desktop/ Comp_Graphics/Breakout/Resources/Shaders/default.frag", nullptr);

    //Configure Shaders

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
                        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    shader.Activate();
    shader.setInt("image", 0);
    shader.setMat4("projection", projection);

    Renderer = new SpriteRenderer(shader);

    
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
    lulu.loadTexture("../Resources/TextureSource/lulu2.png", 0, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
    Renderer->DrawSprite(lulu, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
