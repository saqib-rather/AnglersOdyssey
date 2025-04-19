ParticleSystem::ParticleSystem(unsigned int count) :
    particles(count),
    vertices(sf::Points, count),
    lifetime(sf::seconds(1.5f)) {
}

void ParticleSystem::update(float dt) {
    for (size_t i = 0; i < particles.size(); ++i) {
        Particle& p = particles[i];
        p.lifetime -= sf::seconds(dt);

        if (p.lifetime <= sf::Time::Zero)
            resetParticle(i);

        vertices[i].position += p.velocity * dt;
        float ratio = p.lifetime.asSeconds() / lifetime.asSeconds();
        vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
    }
}

void ParticleSystem::resetParticle(size_t index) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> angle(0.0f, 360.0f);
    std::uniform_real_distribution<float> speed(50.0f, 150.0f);
    
    float radians = angle(rng) * 3.14f / 180.0f;
    particles[index].velocity = sf::Vector2f(
        std::cos(radians) * speed(rng),
        std::sin(radians) * speed(rng)
    );
    particles[index].lifetime = sf::milliseconds(
        std::uniform_int_distribution<>(500, 1500)(rng));
    
    vertices[index].color = sf::Color(255, 255, 255, 255);
}
