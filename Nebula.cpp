#include "Nebula.h"

Nebula::Nebula(float x, float y, float radius, float slowdown) 
    : position(x, y), radius(radius), slowdownFactor(slowdown) {
    
    shape.setRadius(radius);
    shape.setPosition(x - radius, y - radius);
    shape.setFillColor(sf::Color(50, 0, 100, 120));
    shape.setOutlineThickness(2.0f);
    shape.setOutlineColor(sf::Color(150, 50, 200, 180));
}

Vector2 Nebula::getPosition() const {
    return position;
}

float Nebula::getRadius() const {
    return radius;
}

float Nebula::getSlowdownFactor() const {
    return slowdownFactor;
}

bool Nebula::isInside(const Vector2& pos) const {
    Vector2 distance = position - pos;
    return distance.length() <= radius;
}

void Nebula::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}