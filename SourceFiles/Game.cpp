#include "Game.h"
#include "SpriteRenderer.h"
#include "shaderClass.h"
#include "Texture.h"
#include "ResourceManager.h"

// Game-related state data
SpriteRenderer*         Renderer;
GameObject*             Player;


// Initial size of player paddle
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of player paddle
const float PLAYER_VELOCITY(500.0f);

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
     // Load Shaders
    ResourceManager::LoadShader("Resources/Shaders/default.vert", "Resources/Shaders/default.frag", nullptr, "ShaderProgram");

    // Initialize projection matrix and configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
                        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("ShaderProgram").Activate();
    ResourceManager::GetShader("ShaderProgram").setInt("image", 0);
    ResourceManager::GetShader("ShaderProgram").setMat4("projection", projection);
    Renderer = new SpriteRenderer(ResourceManager::GetShader("ShaderProgram"));


    // Load Textures
    ResourceManager::LoadTexture("background", "Resources/TextureSource/background.jpg");
    ResourceManager::LoadTexture("face", "Resources/TextureSource/awesomeface.png");
    ResourceManager::LoadTexture("block", "Resources/TextureSource/block.png");
    ResourceManager::LoadTexture("block_solid", "Resources/TextureSource/block_solid.png");
    ResourceManager::LoadTexture("paddle", "Resources/TextureSource/paddle.png");


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

    // Configure player paddle game object
    glm::vec2 playerPos = glm::vec2( (this->Width / 2.0f) - (PLAYER_SIZE.x / 2.0f) , (this->Height - PLAYER_SIZE.y) );
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

   

    
    
}

// Processes input for paddle movement
void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        // Move playerboard
        if (this->Keys[GLFW_KEY_A]) // When 'a' key is pressed
            {
                if (Player->Position.x >=0.0f)  // If the left side of the paddle is to the right of the left border
                    {
                        Player->Position.x -= velocity;
                    }
            }
        if (this->Keys[GLFW_KEY_D]) // When 'd' key is pressed
            {
                if (Player->Position.x <= this->Width - Player->Size.x)// If the right side of the paddle is left of the right border
                {
                    Player->Position.x += velocity;
                }
            }
    }
}

void Game::Update(float dt)
{

}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        // Draw the background
        Renderer->DrawSprite(ResourceManager::GetTexture("background"),
            glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
        
        // Draw the level
        this->Levels[this->Level].Draw(*Renderer);
        // Draw the player paddle
        Player->Draw(*Renderer);
    }
    

}
