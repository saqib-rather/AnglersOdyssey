#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Fish.h"
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void spawnFish();
    void checkCollisions();

    sf::RenderWindow window;
    Player player;
    std::vector<Fish> fishes;
    sf::Clock fishSpawnClock;
    
    // Resources
    sf::Texture playerTexture;
    sf::Texture fishTexture;
    sf::Font font;
    sf::Text scoreText;
    sf::Text levelText;
    
    // Audio
    sf::SoundBuffer catchSoundBuffer;
    sf::Sound catchSound;
    sf::Music bgMusic;
    
    // Game state
    int score;
    int level;
    float gameSpeed;
};
