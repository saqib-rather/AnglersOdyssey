#include "Hook.h"

Hook::Hook() : 
    maxDepth(700.0f),
    currentDepth(0.0f),
    isCasting(false),
    reelSpeed(400.0f) {
    
    line.setFillColor(sf::Color(200, 200, 200));
    hook.setFillColor(sf::Color(100, 100, 100));
    hook.setRadius(5.0f);
    hook.setOrigin(5.0f, 5.0f);
}

void Hook::cast(float power) {
    isCasting = true;
    currentDepth = maxDepth * power;
    startPosition = {getPosition().x, getPosition().y};
}

void Hook::update(float deltaTime) {
    if (isCasting) {
        // Move hook downward
        float targetY = startPosition.y + currentDepth;
        if (getPosition().y < targetY) {
            move(0, reelSpeed * deltaTime);
        }
        
        // Update line
        line.setPosition(startPosition);
        line.setSize(sf::Vector2f(2.0f, getPosition().y - startPosition.y));
    }
}

void Hook::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (isCasting) {
        target.draw(line, states);
        target.draw(hook, states);
    }
}
