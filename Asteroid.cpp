#include "Asteroid.h"
#include <algorithm>

Asteroid::Asteroid(float x, float y, float radius, float gravity) 
    : position(x, y), radius(radius), gravityStrength(gravity) {
    
    shape.setRadius(radius);
    shape.setPosition(x - radius, y - radius);
    shape.setFillColor(sf::Color(80, 80, 80));
    shape.setOutlineThickness(3.0f);
    shape.setOutlineColor(sf::Color::White);
}

Vector2 Asteroid::getPosition() const {
    return position;
}

float Asteroid::getRadius() const {
    return radius;
}

float Asteroid::getGravityStrength() const {
    return gravityStrength;
}

Vector2 Asteroid::getGravityForce(const Vector2& targetPos, float targetMass) const {
    Vector2 direction = position - targetPos;
    float distance = direction.length();
    
    distance = std::max(distance, 1.0f); // минимальная дистанция грав. взаимодействия, тк F~1/r^2
    
    float force = (gravityStrength * targetMass * 85.0f) / (distance * distance);
    return direction.normalized() * force;
}

void Asteroid::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

bool Asteroid::contains(const Vector2& point) const {
    Vector2 diff = position - point;
    return diff.length() <= radius;
}

bool Asteroid::checkCollision(const Vector2& point, float pointRadius) const {
    Vector2 diff = position - point;
    return diff.length() <= (radius + pointRadius);
}