class Hook : public sf::Drawable {
public:
    Hook();
    void update(float deltaTime);
    void cast(float power);
    void reset();
    sf::FloatRect getGlobalBounds() const;
    
private:
    sf::RectangleShape line;
    sf::CircleShape hook;
    sf::Vector2f startPosition;
    bool isCasting;
    float currentDepth;
    float maxDepth;
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

