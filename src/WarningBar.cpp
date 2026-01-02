#include "class/WarningBar.hpp"
#include "class/Game.hpp"

raylib::Color WarningBar::convertTypeToColor(std::string type) const {
    if (type == "ARROW")   return {200, 0, 20};
    if (type == "HOMING")  return {0, 200, 0};
    if (type == "BOULDER") return {0, 0, 230};
    return {200, 0, 20};
}

raylib::Vector2 WarningBar::convertSideToCenter(std::string side) const {
    if (side == "LEFT")   return raylib::Vector2(20, GetScreenHeight()/2);
    if (side == "TOP")    return raylib::Vector2(GetScreenWidth()/2, 20);
    if (side == "RIGHT")  return raylib::Vector2(GetScreenWidth() - 20, GetScreenHeight()/2);
    if (side == "BOTTOM") return raylib::Vector2(GetScreenWidth()/2, GetScreenHeight() - 20);
    return raylib::Vector2(20, GetScreenHeight()/2);
}

raylib::Vector2 WarningBar::convertTypeToDimension(std::string type) const {
    raylib::Vector2 dim;
    float length = 370;
    if (type == "ARROW")  length *= 2;
    if (type == "HOMING") length *= 1.5;
    dim.x = 15;
    dim.y = length;
    if (!this->isVertical) {
        dim.y = dim.x;
        dim.x = length;
    }
    return dim;
}

WarningBar::WarningBar() : color(WHITE), center(0,0), dimension(20, 40), isVertical(true)  {
    this->lifeTime = Timer(0.3, 0);
    this->position.x = -111;
}

WarningBar::WarningBar(Event event) : color(convertTypeToColor(event.type)), isVertical(true),
    center(convertSideToCenter(event.side)) {
    this->lifeTime = Timer(0.3, 0);
    if (event.side == "TOP" || event.side == "BOTTOM") (isVertical = false);
    this->dimension = convertTypeToDimension(event.type);
    this->position.x = -111;
}

void WarningBar::spawn(raylib::Vector2 position, raylib::Vector2 direction) {
    this->lifeTime.activate();
}

void WarningBar::update(float deltaTime) {
    Entity::update(deltaTime);
}

void WarningBar::draw() {
    DrawRectangleRec(Game::rectangleFromCenterPoint(center, dimension.x, dimension.y), color);
}
