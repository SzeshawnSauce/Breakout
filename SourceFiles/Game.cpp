#include <tuple>

#include "Game.h"
#include "GameObject.h"
#include "GameLevel.h"
#include "SpriteRenderer.h"
#include "shaderClass.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "BallObject.h"

// Initial size of player paddle
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of player paddle
const float PLAYER_VELOCITY(500.0f);
// Initial velocity of the ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const float BALL_RADIUS = 12.5f;


// Aliasing collision results
using Collision = std::tuple<bool, Direction, glm::vec2>;

// Game-related state data
SpriteRenderer*         Renderer;
GameObject*             Player;
BallObject*             Ball;

Collision   CheckCollision(BallObject& one, GameObject& two);
Direction   VectorDirection(glm::vec2 target);

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
    ResourceManager::LoadTexture("awesomeface", "Resources/TextureSource/awesomeface.png");


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

    // Configure ball game object

    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("awesomeface"));
    
    
}

// Processes input for paddle movement
void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        // Move playerboard
        if (this->Keys[GLFW_KEY_A]) // Moves left when 'a' key is pressed
            {
                if (Player->Position.x >=0.0f)  // If the left side of the paddle is to the right of the left border
                    {
                        Player->Position.x -= velocity;
                        if (Ball->Stuck)
                        {
                            Ball->Position.x -= velocity;
                        }
                    }
            }
        if (this->Keys[GLFW_KEY_D]) // Moves right when 'd' key is pressed
            {
                if (Player->Position.x <= this->Width - Player->Size.x)// If the right side of the paddle is left of the right border
                {
                    Player->Position.x += velocity;
                    if (Ball->Stuck)
                        {
                            Ball->Position.x += velocity;
                        }
                }
            }
        if (this->Keys[GLFW_KEY_SPACE]) // Releases ball from paddle when space is pressed
        {
            Ball->Stuck = false;
        }
    }
}

void Game::Update(float dt)
{
    // Update ball object
    Ball->Move(dt, this->Width);
    this->DoCollisions();
    if (Ball->Position.y >= this->Height)
    {
        this->ResetLevel();
        this->ResetPlayer();
    }
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

        // Draw the ball
        Ball->Draw(*Renderer);
    }
}

void Game::DoCollisions()
{
    for (GameObject& box : this->Levels[this->Level].Bricks)
    {
        if (!box.IsDestroyed)
        {
            Collision collision = CheckCollision(*Ball, box);
            if (std::get<0>(collision))
            {
                if (!box.IsSolid) // Destory box if solid
                {
                    box.IsDestroyed = true;
                }
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == LEFT || dir == RIGHT) // Horizontal collisions
                {
                    Ball->Velocity.x = -(Ball->Velocity.x); // Reverse horizontal velocity 
                    float penetration = Ball->Radius - std::abs(diff_vector.x);
                    if (dir == LEFT)
                    {
                        Ball->Position.x += penetration; // if the ball comes from the left bounce back left
                    }
                    else
                    {
                        Ball->Position.x -= penetration; // if the ball comes from the right bounce back right
                    }

                }
                else // Vertical collisions
                {
                    Ball->Velocity.y = -(Ball->Velocity.y); // Reverse vertical velocity
                    float penetration = Ball->Radius - std::abs(diff_vector.y);
                    if(dir == UP)
                    {
                        Ball->Position.y -= penetration; // If the ball comes from below bounce back down
                    }
                    else
                    {
                        Ball->Position.y += penetration; // If the ball comes from above bounce back up
                    }

                }
                
            }
        }
        Collision result = CheckCollision(*Ball, *Player);
        if (!Ball->Stuck && std::get<0>(result))
        {
            // Check where ball hits board and change velocity based on that position
            float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
            float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
            float percentage = distance / (Player->Size.x / 2.0f);

            float strength = 2.0f;
            glm::vec2 oldVelocity = Ball->Velocity;
            Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
            Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y);
            Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
        }
    }
}


Collision CheckCollision(BallObject& one, GameObject& two) //AABB - Circle Collision
{
    // Get the center of the circle
    glm::vec2 circle_center(one.Position + one.Radius);
    
    // Get the difference between circle and rectangle centers
    glm::vec2 half_extents = two.Size / 2.0f;
    glm::vec2 rectangle_center = glm::vec2(two.Position + half_extents);
    glm::vec2 differenceVec = circle_center - (rectangle_center);
    
    // Get the closest point from rectangle to circle
    glm::vec2 clampedVec = glm::clamp(differenceVec, -half_extents, half_extents);
    glm::vec2 closest = rectangle_center + clampedVec;

    // Get the distance between the circle's center and the closest point on the rectangle
    // Check if this distance is less than the circle's radius
    differenceVec = closest - circle_center;
    if (glm::length(differenceVec) <= one.Radius)
    {
        return std::make_tuple(true, VectorDirection(differenceVec), differenceVec);
    }
    else
    {
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
    }
    
}


Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] =
    {
        glm::vec2(0.0f, 1.0f), // UP
        glm::vec2(0.0f, -1.0f), // DOWN
        glm::vec2(-1.0f, 0.0f), // LEFT
        glm::vec2(1.0f, 0.0f) // RIGHT
    };

    float max = 0.0f;
    unsigned int best_match = -1;
    for(unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}

void Game::ResetLevel()
{
    if (this->Level == 0)
        this->Levels[0].Load("Resources/Levels/level1.lvl", this->Width, this->Height / 2);
    else if (this->Level == 1)
        this->Levels[1].Load("Resources/Levels/level2.lvl", this->Width, this->Height / 2);
    else if (this->Level == 2)
        this->Levels[2].Load("Resources/Levels/level3.lvl", this->Width, this->Height / 2);
    else if (this->Level == 3)
        this->Levels[3].Load("Resources/Levels/level4.lvl", this->Width, this->Height / 2);
}

void Game::ResetPlayer()
{
    Player->Position = glm::vec2( (this->Width / 2.0f) - (PLAYER_SIZE.x / 2.0f) , (this->Height - PLAYER_SIZE.y) );
    Ball->Reset((Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
}

 
