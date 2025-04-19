#include "Fish.h"
#include <random>

std::map<FishType, FishData> Fish::fishDatabase = {
    {FishType::MINNOW, {100, 150.0f, 0.6f, {0, 0, 32, 16}}},
    {FishType::BASS, {250, 120.0f, 0.3f, {32, 0, 32, 24}}},
    {FishType::SALMON, {500, 180.0f, 0.1f, {64, 0, 48, 24}}},
    {FishType::SHARK, {1000, 200.0f, 0.05f, {112, 0, 64, 32}}}
};

Fish::Fish(FishType type) : 
    type(type),
    speed(fishDatabase[type].speed),
    removeFlag(false),
    animationFrame(0) {
    
    setTextureRect(fishDatabase[type].textureRect);
    setScale(2.0f, 2.0f);
    
    // Random vertical position
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> yDist(400.0f, 600.0f);
    setPosition(1300, yDist(rng));
}

void Fish::update(float deltaTime) {
    move(-speed * deltaTime, 0);
    
    // Animation
    static float animTimer = 0.0f;
    animTimer += deltaTime;
    if (animTimer > 0.2f) {
        animationFrame = (animationFrame + 1) % 2;
        setTextureRect({
            fishDatabase[type].textureRect.left + animationFrame * fishDatabase[type].textureRect.width,
            fishDatabase[type].textureRect.top,
            fishDatabase[type].textureRect.width,
            fishDatabase[type].textureRect.height
        });
        animTimer = 0.0f;
    }
}
