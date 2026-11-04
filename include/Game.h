#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SpriteRenderer.h"

// Current state of the game
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_LOSE
};


class Game
{
public:

    // Game State
    GameState       State;
    bool            Keys[1024];
    unsigned int    Width, Height;
    SpriteRenderer  *Renderer;
    Shader          shader;

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
