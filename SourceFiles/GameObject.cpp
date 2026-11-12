#include "GameObject.h"

GameObject::GameObject() : 
    Position(0.0f, 0.0f), Size(1.0f,1.0f), Velocity(0.0f), Color(1.0f),
    Rotation(0.0f), Sprite(), IsSolid(false), IsDestroyed(false) {}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color, glm::vec2 velocity)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), IsDestroyed(false) {}

void GameObject::Draw(SpriteRenderer &renderer)
    {
        renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
    }

static bool CheckCollision(GameObject& one, GameObject& two)
    {
    // Check Collision on X-axis
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    // Check Collosion on Y-axis
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    
    return collisionX && collisionY;
    }
