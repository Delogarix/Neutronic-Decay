
#include "class/Game.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif



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
    DrawText(TextFormat("%f", sequencer.getTimeElapsed()), GetScreenWidth()/2 - 60, 8, 30, WHITE);
    DrawText(TextFormat("%i", player.getHeath()), GetScreenWidth()/2 - 11, 60, 20, VIOLET);
}

void Game::drawFrame() {
    constexpr float thickness = 65;
    DrawLineEx(topRight, rightCorner, thickness, BLACK);
    DrawLineEx(bottomLeft, rightCorner, thickness, BLACK);
    DrawLineEx(topRight, leftCorner, thickness, BLACK);
    DrawLineEx(leftCorner, bottomLeft, thickness, BLACK);
    DrawCircleV(leftCorner, 10, BLACK);
    DrawCircleV(rightCorner, 10, BLACK);
    DrawCircleV(topRight, 10, BLACK);
    DrawCircleV(bottomLeft, 10, BLACK);
}

void Game::reStart() {
    flushObjects();
    sequencer.reStart();
    player = Player(iridiumS, boxLength/2);
}

Game::Game() : boxLength(GetScreenHeight() - 15), leftCorner(raylib::Vector2(((GetScreenHeight() - boxLength)/2), ((GetScreenHeight() - boxLength)/2))),
rightCorner(raylib::Vector2(GetScreenHeight() - (GetScreenHeight() - boxLength)/2, GetScreenHeight() - (GetScreenHeight() - boxLength)/2)),
topRight(raylib::Vector2(rightCorner.x, leftCorner.x)), bottomLeft(raylib::Vector2(leftCorner.x, rightCorner.y)),
isFreezed(false), sequencer("wave/wave_60.txt", this) {
    for (unsigned int i = 0; i < MAXOBJECTS; i++) {
        this->objects[i] = nullptr;
    }
    player = Player(iridiumS, boxLength/2);
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
}


void Game::update(float deltaTime) {


    if (IsKeyPressed(KEY_P)) isFreezed = !isFreezed;

    if (IsKeyPressed(KEY_R)) reStart();

    if (IsKeyPressed(KEY_T)) {
        std::cout << "NETWORK: Sending score to php : " << sequencer.getTimeElapsed() << std::endl;
        #if defined(PLATFORM_WEB)
            //std::cout << "PLATFORM WEB :" << std::endl;
            float finalScore = sequencer.getTimeElapsed();
            EM_ASM({
            console.log('I received: ' + $0);
            fetch("../server/api_score.php",
            {
                method: "POST",
                body: JSON.stringify({score: $0})
            }).then(function(res){ console.log(res); }).catch(function(res){ console.log(res + "Catch") })
            }, finalScore);
        #endif
    }

    if (!isFreezed) {
        if (player.isDead()) reStart();
        if (!sequencer.levelDone()) {
            sequencer.update(deltaTime);
        } else {
            //std::cout << "GG !!!!!" << std::endl;

        }

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
    drawFrame();
    displayGameInfo();

}

Entity * Game::convertTypeToBullet(std::string type) {
    Entity *newObject = nullptr;
    if (type == "ARROW") newObject = new Arrow(redArrowS, 600);
    else if (type == "HOMING") newObject = new Homing(homingElecS, &player);
    else if (type == "BOULDER") newObject = new Arrow(boulderS, 150, 68);
    else { std::cout << "ERROR: Wrong bullet type read : " << type << std::endl; }
    return newObject;
}

raylib::Vector2 Game::convertSideToVector(std::string side) {
    raylib::Vector2 vec = ZERO;
    if      (side == "LEFT")   vec = raylib::Vector2(leftCorner.x, GetRandomValue(leftCorner.y, bottomLeft.y));
    else if (side == "TOP")    vec = raylib::Vector2(GetRandomValue(leftCorner.x, topRight.x), leftCorner.y);
    else if (side == "RIGHT")  vec = raylib::Vector2(topRight.x, GetRandomValue(topRight.y, rightCorner.y));
    else if (side == "BOTTOM") vec = raylib::Vector2(GetRandomValue(bottomLeft.x, rightCorner.x), rightCorner.y);
    else vec = raylib::Vector2(GetRandomValue(leftCorner.x, topRight.x), leftCorner.y);
    return vec;
}

std::string Game::getRandomSide() {
    int side = GetRandomValue(0, 3); // LEFT - TOP - RIGHT - BOTTOM
    if (side == 0) return "LEFT";
    if (side == 1) return "TOP";
    if (side == 2) return "RIGHT";
    if (side == 3) return "BOTTOM";
    return "TOP";
}

void Game::spawnBullet(Entity *bullet, Event event) {
    raylib::Vector2 spawnPoint = convertSideToVector(event.side);
    raylib::Vector2 targetDirection = player.getPosition() - spawnPoint;
    targetDirection = offsetVectorAngle(targetDirection, 20);
    if (bullet != nullptr) {
        unsigned int i = getFreeIndex();
        if (i != -1) {
            bullet->spawn(spawnPoint, targetDirection);
            objects[i] = bullet;
        }
    }
    else std::cout << "WARNING: Trying to spawn a nullptr bullet" << std::endl;

}

void Game::spawnBullets(Event event) {
    for (unsigned int i = 0; i < event.amount; i++) {
        Entity *newBullet = convertTypeToBullet(event.type);
        spawnBullet(newBullet, event);
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
