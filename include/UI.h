class UI {
public:
    UI();
    void update(int score, int level, float castingPower);
    void draw(sf::RenderWindow& window);
    
private:
    sf::Font font;
    sf::Text scoreText;
    sf::Text levelText;
    sf::RectangleShape powerBar;
    sf::RectangleShape powerBarOutline;
};
