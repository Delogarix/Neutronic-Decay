#include "class/AnimatedSprite.hpp"
#include <iostream>

// CONSTRUCTOR - - - - - - - - - -

AnimatedSprite::AnimatedSprite()
    : texture(nullptr), scale(1.0f), rotation(0.0f), rotationOffset(0.0f), lookDirection(BASEVECTOR), framePerLine(1),
      lineNumber(1), frameWidth(0), frameHeight(0), currentFrame(0), currentLine(0), frameDelta(0), frameRate(1)
{ }

AnimatedSprite::AnimatedSprite(raylib::Texture *texture, float scale, float rotationOffset) : texture(texture),
    scale(scale), rotation(0), rotationOffset(rotationOffset), lookDirection(BASEVECTOR), framePerLine(1), lineNumber(1), frameWidth(texture->width), frameHeight(texture->height),
    currentFrame(1), currentLine(1), frameDelta(0), frameRate(0)
{ }

AnimatedSprite::AnimatedSprite(raylib::Texture *texture, unsigned int framePerLine, unsigned int lineNumber)
    : texture(texture), scale(1), rotation(0), rotationOffset(PI/7), lookDirection(BASEVECTOR), framePerLine(framePerLine),
    lineNumber(lineNumber), frameWidth(texture->width/framePerLine), frameHeight(texture->height/lineNumber), currentFrame(1), currentLine(1),
    frameDelta(0), frameRate(1)
{ }

AnimatedSprite::AnimatedSprite(raylib::Texture *texture, float scale, float rotationOffset, float framePerSecond, float framePerLine, float lineNumber)
    : texture(texture), scale(scale), rotation(0), rotationOffset(rotationOffset), lookDirection(BASEVECTOR), framePerLine(framePerLine), lineNumber(lineNumber),
    frameWidth(texture->width/framePerLine), frameHeight(texture->height/lineNumber), currentFrame(1), currentLine(1), frameDelta(0), frameRate(framePerSecond)
{ }

// GETTER / SETTER - - - - - - - - - -

raylib::Vector2 AnimatedSprite::getLookDirection() const { return this->lookDirection; }

// METHODS - - - - - - - - - -

void AnimatedSprite::update(float deltaTime) {
    if (frameDelta >= 1) {
        currentFrame++;
        frameDelta = 0;
    }
    if (currentFrame > framePerLine) {
        currentFrame = 1;
        currentLine++;
    }
    if (currentLine > lineNumber) {
        currentLine = 1;
    }
    frameDelta += deltaTime * frameRate;
}

void AnimatedSprite::draw(const raylib::Vector2 position) {
    if (texture != nullptr) {

        rotation = BASEVECTOR.Rotate(rotationOffset).Angle(lookDirection);

        raylib::Rectangle source = { frameWidth * (currentFrame - 1), frameHeight * (currentLine - 1), frameWidth, frameHeight};
        raylib::Rectangle dest = { position.x , position.y , frameWidth * scale, frameHeight * scale}; //170
        raylib::Vector2 origin = { frameWidth * scale/2, frameHeight * scale/2 };

        DrawTexturePro(*texture, source, dest, origin, rotation * RAD2DEG, WHITE);

    }
}

void AnimatedSprite::drawDirection(raylib::Vector2 position) {
    //Game::displayVector(this->lookDirection.Normalize().Scale(200), position, BLUE);
}

void AnimatedSprite::setTexture(raylib::Texture *texture) {
    this->texture = texture;
}

void AnimatedSprite::setScale(float scale) {
    this->scale = scale;
}

void AnimatedSprite::lookAt(raylib::Vector2 lookDirection) {
    this->lookDirection = lookDirection;
}

void AnimatedSprite::rotate(float angle) {
    this->lookDirection = this->lookDirection.Rotate(angle * DEG2RAD);
}

void AnimatedSprite::setFramePerSecond(float frameRate) {
    this->frameRate = frameRate;
}

