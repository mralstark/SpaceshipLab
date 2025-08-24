#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Vector2.h"

struct Particle {
    Vector2 position;
    Vector2 velocity;
    sf::Color color;
    float lifeTime;
    float maxLifeTime;
    float size;
};

class Explosion {
private:
    std::vector<Particle> particles;
    Vector2 center;
    float duration;
    float maxDuration;
    bool active;

public:
    Explosion();
    
    void start(const Vector2& position);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    
    bool isActive() const;
    bool isFinished() const;
};

#endif