#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::Sprite {
public:
    Player();
    void update(float deltaTime);
    void castLine();
    
private:
    float speed;
    bool isCasting;
};
