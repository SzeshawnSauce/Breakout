#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "GameLevel.h"
#include "ResourceManager.h"


// Loads level from file
void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    // Clear old data
    this->Bricks.clear();

    // Load from file
    unsigned int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;
    if(fstream)
    {
        while (std::getline(fstream, line)) // Read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;

            while(sstream >> tileCode) // Read each word separated by spaces
            {    
                row.push_back(tileCode); // Store each word into a row
            }

            tileData.push_back(row); // Store the finished row into the tile data
        }

            if(tileData.size() > 0) // Initialize the game level if we successfully read the data file;
            {
                this->init(tileData, levelWidth, levelHeight);
            }

        
    }
    else
    {
        std::cout << "UNABLE TO READ GAME DATA FILE";
    }

}

// Render Level
void GameLevel::Draw(SpriteRenderer &renderer)
{
    for(GameObject &tile : this->Bricks)
    {
        if(!tile.IsDestroyed)
        {
            tile.Draw(renderer);
        }
    }
}

// Check if level is completed (all non-solid tiles are destroyed)
bool GameLevel::IsCompleted()
{
    for(GameObject &tile : this->Bricks)
    {
        if(!tile.IsSolid && !tile.IsDestroyed)
        {
            return false;
        }
    }
    return true;
}


void GameLevel::init(std::vector<std::vector<unsigned int>> tileData,
                unsigned int levelWidth, unsigned int levelHeight)
                {
                    // Calculate game level dimensions
                    unsigned int height = tileData.size();
                    unsigned int width = tileData[0].size();
                    float unit_width = levelWidth / static_cast<float>(width);
                    float unit_height = levelHeight / static_cast<float>(height);
                    
                    // Initialize level tile based on tileData
                    for(unsigned int y = 0; y < height; ++y)
                    {
                        for(unsigned int x = 0; x < width; ++x)
                        {
                            // Check block type from level data (2D level array)
                            if(tileData[y][x] == 1) // Solid
                            {
                                glm::vec2 pos(unit_width * x, unit_height * y); // Gets position of the block based on what order it comes in and the size of the blocks
                                glm::vec2 size(unit_width, unit_height); // Size of blocks are determined by number of blocks in each row and column
                                GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f)); // Creates the actual game block object
                                obj.IsSolid = true;
                                this->Bricks.push_back(obj); // Store into Bricks container
                            }
                            else if(tileData[y][x] > 1) // Non-solid breakable block
                            {
                                glm::vec3 color = glm::vec3(1.0f); // Originally: White
                                if (tileData[y][x] == 2)
                                {
                                    color = glm::vec3(0.2f, 0.6f, 1.0f); 
                                }
                                else if(tileData[y][x] == 3)
                                {
                                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                                }
                                else if (tileData[y][x] == 4)
                                {
                                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                                }
                                else if (tileData[y][x] == 5)
                                {
                                    color = glm::vec3(1.0f, 0.5f, 0.0f);
                                }
                                glm::vec2 pos(unit_width * x, unit_height * y);
                                glm::vec2 size(unit_width, unit_height);
                                this->Bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture("block"), color));
                            }
                        }
                    }
                }

