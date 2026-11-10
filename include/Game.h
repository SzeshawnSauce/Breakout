#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "GameLevel.h"



// Represents current state of the game
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_LOSE
};


// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
    public:

        // Game State
        GameState               State;
        bool                    Keys[1024];
        unsigned int            Width, Height;
        std::vector<GameLevel>  Levels;
        unsigned int            Level;

        // Constructor/Destructor
        Game(unsigned int width, unsigned int height);
        ~Game();

        // Initializes the game (loads shaders/textures/levels)
        void Init();
        
        // Game Loop
        void ProcessInput(float dt);
        void Update(float dt);
        void Render();
};

#endif
