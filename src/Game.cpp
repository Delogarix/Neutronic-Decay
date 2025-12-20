
#include "class/Game.hpp"



unsigned int Game::getFreeIndex() {
    for (int i = 0; i < MAXOBJECTS; i++) {
        if (objects[i] == nullptr) {
            return i;
        }
    }
    std::cout << "No more space in objects lists!" << std::endl;
    return -1;
}

void Game::resolveCollision(Entity *player, Entity *&bullet) {
    if (bullet != nullptr && player->isColliding(bullet) && player != bullet) {
        delete bullet;
        bullet = nullptr;
    }
}

Game::Game() : boxLength(800), isFreezed(false) , sequencer("wave/wave1.txt", this){
    for (unsigned int i = 0; i < MAXOBJECTS; i++) {
        this->objects[i] = nullptr;
    }
    objects[0] = &player; // The first object is the player ptr
}

void Game::init() { // Needs to be called after window is created
    iridiumTex = LoadTexture("assets/iridium-core.png");
    redArrowTex = LoadTexture("assets/red-arrow.png");
    homingElecTex = LoadTexture("assets/homing-elec.png");
    boulderTex = LoadTexture("assets/red-arrow.png"); // temp test
    iridiumS = AnimatedSprite(&iridiumTex, 6, 0, 3.6f, 5, 1);
    redArrowS = AnimatedSprite(&redArrowTex, 2, PI/4, 9.5f, 5, 1);
    homingElecS = AnimatedSprite(&homingElecTex, 2, 0, 13.0f, 7, 1);
    boulderS = AnimatedSprite(&homingElecTex, 5, 0, 13.0f, 7, 1);
    player.sprite = iridiumS;
    sequencer.start();
}


void Game::update(float deltaTime) {

    sequencer.update(deltaTime);

    if (IsKeyPressed(KEY_P)) isFreezed = !isFreezed;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        bulletRandomWave(&player);
    }

    for (unsigned int i = 0; i < MAXOBJECTS; i++) {
        if (objects[i] != nullptr && !isFreezed) {
            objects[i]->update(deltaTime);
            resolveCollision(&player, objects[i]);
        }
    }
}

void Game::draw() {
    for (unsigned int i = 0; i < MAXOBJECTS; i++) {
        if (objects[i] != nullptr) {
            objects[i]->draw();
            //objects[i]->drawHitbox();
        }
    }
}

void Game::bulletRandomWave(Entity *target) {
    raylib::Vector2 spawnPoint, targetDirection;
    int side = GetRandomValue(0, 3); // LEFT - UP - RIGHT - DOWN
    int bulletType = GetRandomValue(0, 2);
    if (side == 0) spawnPoint = raylib::Vector2(0, GetRandomValue(0, GetScreenHeight()));
    if (side == 1) spawnPoint = raylib::Vector2(GetRandomValue(0, GetScreenWidth()), 0);
    if (side == 2) spawnPoint = raylib::Vector2(GetScreenWidth(), GetRandomValue(0, GetScreenHeight()));
    if (side == 3) spawnPoint = raylib::Vector2(GetRandomValue(0, GetScreenWidth()), GetScreenHeight());
    targetDirection = target->position - spawnPoint;

    int i = getFreeIndex();
    if (bulletType != 0) objects[i] = new Arrow(redArrowS, 900);
    else objects[i] = new Homing(homingElecS, target);
    targetDirection = offsetVectorAngle(targetDirection, 15);
    objects[i]->spawn(spawnPoint, targetDirection);
}

raylib::Vector2 Game::getRandomVector() {
    raylib::Vector2 vec = UP;
    float angle = GetRandomValue(0, 360);
    vec = vec.Rotate(angle * DEG2RAD);
    return vec;
}

raylib::Vector2 Game::offsetVectorAngle(const raylib::Vector2 &sourceVec, float angle) {
    float randomAngle = GetRandomValue(-angle, angle) * DEG2RAD;
    raylib::Vector2 newVector = sourceVec.Rotate(randomAngle);
    return newVector;
}
