#pragma once
#include "Entity.hpp"
#include "Timer.hpp"
#include "Sequencer.hpp"

class Game;

class WarningBar : public Entity {

    raylib::Color color;
    bool isVertical;
    raylib::Vector2 center, dimension;


    raylib::Color convertTypeToColor(std::string type) const;
    raylib::Vector2 convertSideToCenter(std::string side) const;
    raylib::Vector2 convertTypeToDimension(std::string type) const;

public:

    WarningBar();
    WarningBar(Event event);

    void spawn(raylib::Vector2 position, raylib::Vector2 direction) override;

    void update(float deltaTime) override;

    void draw() override;

};

