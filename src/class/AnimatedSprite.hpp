#pragma once
#include "../../include/raylib-cpp.hpp"

const raylib::Vector2 ZERO = raylib::Vector2(0, 0); // ZERO
const raylib::Vector2 BASEVECTOR = raylib::Vector2(0, -1); // UP
const raylib::Vector2 BASEVECTOR2 = raylib::Vector2(1, 0); // RIGHT

class AnimatedSprite {

    raylib::Texture *texture;

    float scale, rotation, rotationOffset;

    raylib::Vector2 lookDirection;

    float framePerLine, lineNumber;
    float frameWidth, frameHeight;

    float currentFrame, currentLine;
    float frameDelta, frameRate;


public:

    // CONSTRUCTOR
    AnimatedSprite();
    AnimatedSprite(raylib::Texture2D *texture, float scale, float rotationOffset);
    AnimatedSprite(raylib::Texture2D *texture, unsigned int framePerLine, unsigned int lineNumber);
    AnimatedSprite(raylib::Texture2D *texture, float scale, float rotationOffset, float framePerSecond, float framePerLine, float lineNumber);


    // GET SET - - - - -
    [[nodiscard]] raylib::Vector2 getLookDirection() const;

    // METHODS - - - - -
    void update(float deltaTime);
    void draw(raylib::Vector2 position);

    void drawDirection(raylib::Vector2 position);

    void setTexture(raylib::Texture2D *texture);
    void setScale(float scale);
    void lookAt(raylib::Vector2 lookDirection);
    void rotate(float angle); // Angle in degeres
    void setFramePerSecond(float frameRate);

};

