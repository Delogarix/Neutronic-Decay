
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

void Game::flushObjects() {
    for (unsigned int i = 1; i < MAXOBJECTS; i++) {
        if (objects[i] != nullptr) {
            delete objects[i];
            objects[i] = nullptr;
        }
    }
}

void Game::resolveCollision(Entity *player, Entity *&bullet) {
    if (bullet != nullptr && player->isColliding(bullet) && player != bullet) {
        player->onReceivingHit();
        bullet->onGivingHit();
        delete bullet;
        bullet = nullptr;
    }
}

void Game::displayGameInfo() {
    DrawText(TextFormat("%f", sequencer.getTimeElapsed()), GetScreenWidth()/2 - 60, 20, 30, BLACK);
    DrawText(TextFormat("%i", player.getHeath()), GetScreenWidth()/2 - 11, 60, 20, VIOLET);
}

void Game::reStart() {
    flushObjects();
    sequencer.reStart();
    player = Player(iridiumS);
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
    boulderTex = LoadTexture("assets/aqua-sphere.png");
    iridiumS = AnimatedSprite(&iridiumTex, 2, 0, 3.6f, 5, 1);
    redArrowS = AnimatedSprite(&redArrowTex, 2, PI/4, 9.5f, 5, 1);
    homingElecS = AnimatedSprite(&homingElecTex, 2, 0, 13.0f, 7, 1);
    boulderS = AnimatedSprite(&boulderTex, 5, 0, 23.0f, 7, 1);
    player.sprite = iridiumS;
    sequencer.start();

    std::cout << " - [Survive] 60 seconds to win" << std::endl;
    std::cout << " - [ZQSD]    Deplacement" << std::endl;
    std::cout << " - [R]       Recommencer" << std::endl;
    std::cout << " - [P]       Pause" << std::endl;
}


void Game::update(float deltaTime) {


    if (IsKeyPressed(KEY_P)) isFreezed = !isFreezed;

    if (IsKeyPressed(KEY_R)) reStart();

    if (!isFreezed) {
        if (player.isDead()) reStart();
        sequencer.update(deltaTime);
        for (unsigned int i = 0; i < MAXOBJECTS; i++) {
            if (objects[i] != nullptr) {
                objects[i]->update(deltaTime);
                if (objects[i]->lifeTimeExceeded()) {
                    delete objects[i];
                    objects[i] = nullptr;
                }
                resolveCollision(&player, objects[i]);
            }
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
    displayGameInfo();
}

void Game::bulletRandomWave(Entity *target) {
    raylib::Vector2 spawnPoint, targetDirection;
    int side = GetRandomValue(0, 3); // LEFT - UP - RIGHT - DOWN
    int bulletType = GetRandomValue(0, 2);
    if (side == 0) spawnPoint = raylib::Vector2(0, GetRandomValue(0, GetScreenHeight()));
    if (side == 1) spawnPoint = raylib::Vector2(GetRandomValue(0, GetScreenWidth()), 0);
    if (side == 2) spawnPoint = raylib::Vector2(GetScreenWidth(), GetRandomValue(0, GetScreenHeight()));
    if (side == 3) spawnPoint = raylib::Vector2(GetRandomValue(0, GetScreenWidth()), GetScreenHeight());
    targetDirection = target->getPosition() - spawnPoint;

    int i = getFreeIndex();
    if (bulletType != 0) objects[i] = new Arrow(redArrowS, 900);
    else objects[i] = new Homing(homingElecS, target);
    targetDirection = offsetVectorAngle(targetDirection, 15);
    objects[i]->spawn(spawnPoint, targetDirection);
}

Entity * Game::convertTypeToBullet(std::string type) {
    Entity *newObject = nullptr;
    if (type == "ARROW") newObject = new Arrow(redArrowS, 600);
    else if (type == "HOMING") newObject = new Homing(homingElecS, &player);
    else if (type == "BOULDER") newObject = new Arrow(boulderS, 150, 68);
    else { std::cout << "ERROR: Wrong bullet type read : " << type << std::endl; }
    return newObject;
}

void Game::spawnBullet(Entity *bullet) {
    raylib::Vector2 spawnPoint;
    int side = GetRandomValue(0, 3); // LEFT - UP - RIGHT - DOWN
    if (side == 0) spawnPoint = raylib::Vector2(0, GetRandomValue(0, GetScreenHeight()));
    if (side == 1) spawnPoint = raylib::Vector2(GetRandomValue(0, GetScreenWidth()), 0);
    if (side == 2) spawnPoint = raylib::Vector2(GetScreenWidth(), GetRandomValue(0, GetScreenHeight()));
    if (side == 3) spawnPoint = raylib::Vector2(GetRandomValue(0, GetScreenWidth()), GetScreenHeight());
    raylib::Vector2 targetDirection = player.getPosition() - spawnPoint;
    targetDirection = offsetVectorAngle(targetDirection, 15);
    if (bullet != nullptr) {
        unsigned int i = getFreeIndex();
        if (i != -1) {
            bullet->spawn(spawnPoint, targetDirection);
            objects[i] = bullet;
        }

    }
    else std::cout << "WARNING: Trying to spawn a nullptr bullet" << std::endl;

}

void Game::spawnBullets(std::string type, unsigned int amount) {
    for (unsigned int i = 0; i < amount; i++) {
        Entity *newBullet = convertTypeToBullet(type);
        spawnBullet(newBullet);
    }
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
