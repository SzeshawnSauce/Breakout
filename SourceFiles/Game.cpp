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
    // Load Textures
    ResourceManager::LoadTexture("background", "Resources/TextureSource/background.jpg", 0, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
    ResourceManager::LoadTexture("face", "Resources/TextureSource/awesomeface.png", 0, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
    ResourceManager::LoadTexture("block", "Resources/TextureSource/block.png", 0, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
    ResourceManager::LoadTexture("block_solid", "Resources/TextureSource/block_solid.png", 0, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);

    // Load Levels
    GameLevel one;
    one.Load("Resources/Levels/level1.lvl", this->Width, this->Height / 2);
    GameLevel two;
    two.Load("Resources/Levels/level2.lvl", this->Width, this->Height / 2);
    GameLevel three;
    three.Load("Resources/Levels/level3.lvl", this->Width, this->Height / 2);
    GameLevel four;
    four.Load("Resources/Levels/level4.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;

    // Load Shaders
    ResourceManager::LoadShader("Resources/Shaders/default.vert", "Resources/Shaders/default.frag", nullptr, "ShaderProgram");

    // Initialize projection matrix and configure shaders
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
    if(this->State == GAME_ACTIVE)
    {
        // Draw the background
        Renderer->DrawSprite(ResourceManager::GetTexture("background"),
            glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
        
        // Draw the level
        this->Levels[this->Level].Draw(*Renderer);
    }
    

}
