#include "Explosion.h"
#include <random>
#include <cmath>

Explosion::Explosion() : duration(0.0f), maxDuration(2.0f), active(false) {
}

void Explosion::start(const Vector2& position) {
    center = position;
    duration = 0.0f;
    active = true;
    particles.clear();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * 3.14159f);
    std::uniform_real_distribution<float> speedDist(50.0f, 200.0f);
    std::uniform_real_distribution<float> sizeDist(2.0f, 6.0f);
    
    for (int i = 0; i < 50; ++i) {
        Particle particle;
        particle.position = center;
        
        float angle = angleDist(gen);
        float speed = speedDist(gen);
        particle.velocity = Vector2(std::cos(angle) * speed, std::sin(angle) * speed);
        
        if (i < 20) {
            particle.color = sf::Color(255, 100, 0, 255); 
        } else if (i < 35) {
            particle.color = sf::Color(255, 200, 0, 255); 
        } else {
            particle.color = sf::Color(255, 50, 50, 255); 
        }
        
        particle.maxLifeTime = maxDuration * 0.8f;
        particle.lifeTime = particle.maxLifeTime;
        particle.size = sizeDist(gen);
        
        particles.push_back(particle);
    }
}

void Explosion::update(float deltaTime) {
    if (!active) return;
    
    duration += deltaTime;
    
    for (auto& particle : particles) {
        particle.position += particle.velocity * deltaTime;
        particle.lifeTime -= deltaTime;
        
        float alpha = particle.lifeTime / particle.maxLifeTime;
        particle.color.a = static_cast<sf::Uint8>(255 * alpha);
        
        particle.velocity *= 0.98f;
    }
    
    particles.erase(std::remove_if(particles.begin(), particles.end(),
        [](const Particle& p) { return p.lifeTime <= 0; }), particles.end());
    
    if (duration >= maxDuration || particles.empty()) {
        active = false;
    }
}

void Explosion::draw(sf::RenderWindow& window) const {
    if (!active) return;
    
    for (const auto& particle : particles) {
        sf::CircleShape shape(particle.size);
        shape.setPosition(particle.position.x - particle.size, 
                         particle.position.y - particle.size);
        shape.setFillColor(particle.color);
        window.draw(shape);
    }
}

bool Explosion::isActive() const {
    return active;
}

bool Explosion::isFinished() const {
    return !active && duration > 0;
}