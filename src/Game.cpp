#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Angler's Odyssey") {
    // Load textures
    playerTexture.loadFromFile("assets/player.png");
    fishTexture.loadFromFile("assets/fish.png");
    
    // Initialize player
    player.setTexture(playerTexture);
    player.setPosition(400, 500);

    // Initialize UI
    font.loadFromFile("assets/arial.ttf");
    scoreText.setFont(font);
    scoreText.setPosition(10, 10);
    levelText.setFont(font);
    levelText.setPosition(600, 10);

    // Initialize audio
    catchSoundBuffer.loadFromFile("assets/catch.wav");
    catchSound.setBuffer(catchSoundBuffer);
    bgMusic.openFromFile("assets/ocean.ogg");
    bgMusic.setLoop(true);
    bgMusic.play();

    // Game state
    score = 0;
    level = 1;
    gameSpeed = 1.0f;
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float deltaTime) {
    player.update(deltaTime);
    
    // Fish spawning
    if (fishSpawnClock.getElapsedTime().asSeconds() > 2.0f / gameSpeed) {
        spawnFish();
        fishSpawnClock.restart();
    }
    
    // Update fish
    for (auto& fish : fishes) {
        fish.update(deltaTime * gameSpeed);
    }
    
    // Remove off-screen fish
    fishes.erase(std::remove_if(fishes.begin(), fishes.end(),
        [](const Fish& f) { return f.isOffScreen(); }), fishes.end());
    
    checkCollisions();
    
    // Update UI
    scoreText.setString("Score: " + std::to_string(score));
    levelText.setString("Level: " + std::to_string(level));
    
    // Level progression
    if (score > level * 500) {
        level++;
        gameSpeed *= 1.2f;
    }
}

void Game::render() {
    window.clear(sf::Color(30, 144, 255));
    
    // Draw game objects
    player.draw(window);
    for (auto& fish : fishes) {
        fish.draw(window);
    }
    
    // Draw UI
    window.draw(scoreText);
    window.draw(levelText);
    
    window.display();
}

void Game::spawnFish() {
    Fish newFish;
    newFish.setTexture(fishTexture);
    newFish.reset(window.getSize());
    fishes.push_back(newFish);
}

void Game::checkCollisions() {
    for (auto& fish : fishes) {
        if (player.getGlobalBounds().intersects(fish.getGlobalBounds())) {
            catchSound.play();
            score += 50;
            fish.markForRemoval();
        }
    }
}

void Game::handleInput() {
    if (gameState == GameState::PLAYING) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (!isCasting) {
                castingPower = 0.0f;
                isCasting = true;
            }
            castingPower = std::min(castingPower + 0.02f, 1.0f);
        }
        else if (isCasting) {
            player.castLine(castingPower);
            hook.cast(castingPower);
            isCasting = false;
        }
    }
}

void Game::update(float deltaTime) {
    switch(gameState) {
        case GameState::MENU:
            menu.update(window);
            break;
        case GameState::PLAYING:
            player.update(deltaTime);
            hook.update(deltaTime);
            particleSystem.update(deltaTime);
            // ... rest of game logic ...
            break;
        case GameState::GAME_OVER:
            gameOverScreen.update(window);
            break;
    }
}

void Game::handleReeling() {
    if (hook.isFishAttached()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            fishStamina -= reelingPower;
            hook.moveUp();
        }
        if (fishStamina <= 0) {
            catchFish();
        }
    }
}

void Game::loadLevel(int level) {
    currentLevel = level;
    waterCurrentSpeed = 1.0f + (level * 0.1f);
    maxFish = 5 + level * 2;
    rareFishChance = std::min(0.1f + (level * 0.01f), 0.3f);
}

class Inventory {
public:
    void addItem(FishType type);
    void upgradeRod();
    
private:
    std::map<FishType, int> fishCaught;
    int rodLevel;
    float rodStrength;
};

void Game::spawnFish() {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    
    float chance = dist(rng);
    FishType type = FishType::MINNOW;
    
    if (chance < 0.05f) type = FishType::SHARK;
    else if (chance < 0.15f) type = FishType::SALMON;
    else if (chance < 0.45f) type = FishType::BASS;
    
    fishes.emplace_back(type);
}

void Game::checkCollisions() {
    auto& hookPos = hook.getPosition();
    for (auto it = fishes.begin(); it != fishes.end(); ++it) {
        if (it->getGlobalBounds().contains(hookPos)) {
            particleSystem.emit(hookPos);
            score += fishDatabase[it->getType()].scoreValue;
            fishes.erase(it);
            catchSound.play();
            break;
        }
    }
}

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
            
        if (gameState == GameState::MENU) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    gameState = GameState::PLAYING;
                }
            }
        }
    }

    if (gameState == GameState::PLAYING) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (!castingInProgress) {
                castingPower = 0.0f;
                castingInProgress = true;
            }
            castingPower = std::min(castingPower + 0.75f * deltaTime, 1.0f);
        }
        else if (castingInProgress) {
            player.castLine(castingPower);
            hook.cast(castingPower);
            castingInProgress = false;
        }
    }
}
