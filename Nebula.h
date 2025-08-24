#ifndef NEBULA_H
#define NEBULA_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

// Класс туманности
class Nebula {
private:
    Vector2 position;
    float radius;
    float slowdownFactor;
    sf::CircleShape shape;

public:
    Nebula(float x, float y, float radius, float slowdown);
    
    // Геттеры
    Vector2 getPosition() const;
    float getRadius() const;
    float getSlowdownFactor() const;
    
    // Проверяет, находится ли объект внутри туманности
    bool isInside(const Vector2& pos) const;
    
    // Отрисовка
    void draw(sf::RenderWindow& window) const;
};

#endif