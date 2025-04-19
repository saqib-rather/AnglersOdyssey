#pragma once
#include <SFML/Graphics.hpp>

class Fish : public sf::Sprite {
public:
    Fish();
    void update(float deltaTime);
    bool isOffScreen() const;
    void markForRemoval();
    bool shouldRemove() const;
    
private:
    float speed;
    bool removeFlag;
};
enum class FishType { 
    MINNOW, 
    BASS, 
    SALMON, 
    SHARK 
};

struct FishData {
    int scoreValue;
    float speed;
    float rarity;
    sf::IntRect textureRect;
};

class Fish : public sf::Sprite {
public:
    Fish(FishType type);
    // ... existing methods ...
private:
    FishType type;
    static std::map<FishType, FishData> fishDatabase;
};
