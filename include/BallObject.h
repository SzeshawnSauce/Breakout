#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "Texture.h"



// BallObject holds state of the ball object inheriting
// state data from GameObject. Includes functionality that
// was too specific to just use GameObject alone.
class BallObject : public GameObject
{
    public:
        // Ball State
        float Radius;
        bool Stuck;

        // Constructors
        BallObject();
        BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture sprite);

        // Moves the ball within the window bounds (minus bottom edge); returns current position
        glm::vec2 Move(float dt, unsigned int window_width);
        // Resets the ball to original state (on the paddle) with a given position and velocity.
        void      Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif
