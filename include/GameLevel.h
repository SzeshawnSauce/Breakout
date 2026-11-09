#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
#include "GameObject.h"
#include "SpriteRenderer.h"


class GameLevel
{
    public:
    
        // Level State/Container for brick GameObject's
        std::vector<GameObject> Bricks;
        
        // Constructor    
        GameLevel() { } 
        
        // Loads level from file
        void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);

        // Render Level
        void Draw(SpriteRenderer &renderer);

        // Check if level is completed (all non-solid tiles are destroyed)
        bool IsCompleted();

    private:
        
        // Initialize level from tile data
        void init(std::vector<std::vector<unsigned int>> tileData,
                unsigned int levelWidth, unsigned int levelHeight);

};

#endif
