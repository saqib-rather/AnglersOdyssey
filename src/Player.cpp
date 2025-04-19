#include "Player.h"
#include <cmath>

Player::Player() : 
    speed(400.0f), 
    isCasting(false),
    castPower(0.0f),
    animationFrame(0),
    animationTimer(0.0f) {
    
    // Animation setup
    animationFrames = 4;
    frameTime = 0.1f;
}

void Player::update(float deltaTime) {
    // Handle movement
    if (!isCasting) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            move(-speed * deltaTime, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            move(speed * deltaTime, 0);
        }
    }

    // Keep in bounds
    sf::Vector2f pos = getPosition();
    sf::FloatRect bounds = getGlobalBounds();
    if (pos.x < 0) setPosition(0, pos.y);
    if (pos.x > 1280 - bounds.width) 
        setPosition(1280 - bounds.width, pos.y);

    // Update casting animation
    if (isCasting) {
        animationTimer += deltaTime;
        if (animationTimer >= frameTime) {
            animationFrame = (animationFrame + 1) % animationFrames;
            setTextureRect(sf::IntRect(animationFrame * 64, 0, 64, 64));
            animationTimer = 0.0f;
        }
    }
}

void Player::castLine(float power) {
    isCasting = true;
    castPower = power;
    animationFrame = 0;
    setTextureRect(sf::IntRect(0, 0, 64, 64));
}

void Player::resetCast() {
    isCasting = false;
    castPower = 0.0f;
}
