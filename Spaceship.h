#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Vector2.h"
#include "Asteroid.h"
#include "Nebula.h"
#include "Explosion.h"

class Spaceship {
private:
    Vector2 position;
    Vector2 velocity;
    Vector2 spawnPosition;
    float mass;
    float maxSpeed;
    float acceleration;
    sf::CircleShape shape;
    float radius;
    
    int windowWidth;
    int windowHeight;
    
    bool destroyed;
    Explosion explosion;

public:
    Spaceship(float x, float y, int winWidth, int winHeight);
    
    Vector2 getPosition() const;
    Vector2 getVelocity() const;
    float getMass() const;
    float getMaxSpeed() const;
    float getAcceleration() const;
    bool isDestroyed() const;
    
    void setMaxSpeed(float speed);
    void setAcceleration(float accel);
    
    void update(float deltaTime, const sf::Vector2i& mousePos, 
                const std::vector<Asteroid>& asteroids, 
                const std::vector<Nebula>& nebulas);
    
    void draw(sf::RenderWindow& window) const;
    
    void destroy();
    
    bool checkAsteroidCollisions(const std::vector<Asteroid>& asteroids);
    
private:
    void handleScreenBounds();
    
    void applyGravity(const std::vector<Asteroid>& asteroids, float deltaTime);
    
    void applyNebulaEffects(const std::vector<Nebula>& nebulas, float deltaTime);
    
    void moveTowardsMouse(const sf::Vector2i& mousePos, float deltaTime);
    
    void updateVisuals();
    
    void respawn();
};

#endif