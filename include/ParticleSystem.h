class ParticleSystem : public sf::Drawable {
public:
    ParticleSystem(unsigned int count);
    void update(float dt);
    void emit(sf::Vector2f position);
    
private:
    struct Particle {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };
    
    std::vector<Particle> particles;
    sf::VertexArray vertices;
    sf::Time duration;
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void resetParticle(size_t index);
};
