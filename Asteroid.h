#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class Asteroid {
private:
    Vector2 position;
    float radius;
    float gravityStrength;
    sf::CircleShape shape;

public:
    Asteroid(float x, float y, float radius, float gravity);
    
    Vector2 getPosition() const;
    float getRadius() const;
    float getGravityStrength() const;
    
    Vector2 getGravityForce(const Vector2& targetPos, float targetMass) const;
    
    void draw(sf::RenderWindow& window) const;
    
    bool contains(const Vector2& point) const;
    bool checkCollision(const Vector2& point, float pointRadius) const;
};

#endif