void UI::update(int score, int level, float castingPower) {
    scoreText.setString("Score: " + std::to_string(score));
    levelText.setString("Level: " + std::to_string(level));
    
    // Update power bar
    powerBar.setSize(sf::Vector2f(castingPower * 100.0f, 20.0f));
}

void UI::draw(sf::RenderWindow& window) {
    window.draw(scoreText);
    window.draw(levelText);
    window.draw(powerBarOutline);
    window.draw(powerBar);
}
