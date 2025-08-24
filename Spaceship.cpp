#include "Spaceship.h"
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Spaceship::Spaceship(float x, float y, int winWidth, int winHeight) 
    : position(x, y),
      velocity(0, 0),
      spawnPosition(x, y),
      mass(25.0f),
      maxSpeed(100.0f),
      acceleration(100.0f),
      shape(),
      radius(8.0f),
      windowWidth(winWidth),
      windowHeight(winHeight),
      destroyed(false),
      explosion()
{
    shape.setRadius(radius);
    shape.setPosition(x - radius, y - radius);
    shape.setFillColor(sf::Color::Green);
    shape.setPointCount(3);
}

Vector2 Spaceship::getPosition() const {
    return position;
}

Vector2 Spaceship::getVelocity() const {
    return velocity;
}

float Spaceship::getMass() const {
    return mass;
}

float Spaceship::getMaxSpeed() const {
    return maxSpeed;
}

float Spaceship::getAcceleration() const {
    return acceleration;
}

bool Spaceship::isDestroyed() const {
    return destroyed;
}

void Spaceship::setMaxSpeed(float speed) {
    maxSpeed = speed;
}

void Spaceship::setAcceleration(float accel) {
    acceleration = accel;
}

void Spaceship::update(float deltaTime, const sf::Vector2i& mousePos, 
                       const std::vector<Asteroid>& asteroids, 
                       const std::vector<Nebula>& nebulas) {
    
    if (destroyed) {
        explosion.update(deltaTime);
        if (explosion.isFinished()) {
            respawn();
        }
        return;
    }
    
    if (checkAsteroidCollisions(asteroids)) {
        destroy();
        return;
    }
    
    moveTowardsMouse(mousePos, deltaTime);
    
    applyGravity(asteroids, deltaTime);
    
    applyNebulaEffects(nebulas, deltaTime);
    
    if (velocity.length() > maxSpeed) {
        velocity = velocity.normalized() * maxSpeed;
    }
    
    position += velocity * deltaTime;
    
    handleScreenBounds();
    
    updateVisuals();
}

void Spaceship::draw(sf::RenderWindow& window) const {
    if (destroyed) {
        explosion.draw(window);
    } else {
        window.draw(shape);
    }
}

void Spaceship::destroy() {
    destroyed = true;
    explosion.start(position);
}

bool Spaceship::checkAsteroidCollisions(const std::vector<Asteroid>& asteroids) {
    for (const auto& asteroid : asteroids) {
        if (asteroid.checkCollision(position, radius)) {
            return true;
        }
    }
    return false;
}

void Spaceship::respawn() {
    destroyed = false;
    position = spawnPosition;
    velocity = Vector2(0, 0);
    shape.setFillColor(sf::Color::Green);
    updateVisuals();
}

void Spaceship::handleScreenBounds() {
    if (position.x < 0) position.x = static_cast<float>(windowWidth);
    if (position.x > windowWidth) position.x = 0;
    if (position.y < 0) position.y = static_cast<float>(windowHeight);
    if (position.y > windowHeight) position.y = 0;
}

void Spaceship::applyGravity(const std::vector<Asteroid>& asteroids, float deltaTime) {
    for (const auto& asteroid : asteroids) {
        Vector2 gravityForce = asteroid.getGravityForce(position, mass);
        velocity += gravityForce * deltaTime;
    }
}

void Spaceship::applyNebulaEffects(const std::vector<Nebula>& nebulas, float deltaTime) {
    for (const auto& nebula : nebulas) {
        if (nebula.isInside(position)) {
            float slowdownRate = 1.0f - (nebula.getSlowdownFactor() * 3.0f * deltaTime);
            slowdownRate = std::max(slowdownRate, 0.6f); 
            velocity *= slowdownRate;
        }
    }
}

void Spaceship::moveTowardsMouse(const sf::Vector2i& mousePos, float deltaTime) {
    Vector2 mousePosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    Vector2 direction = mousePosition - position;
    
    if (direction.length() > 5.0f) {
        Vector2 targetVelocity = direction.normalized() * acceleration;
        velocity += targetVelocity * deltaTime;
    }
}

void Spaceship::updateVisuals() {
    shape.setPosition(position.x - radius, position.y - radius);
    
    if (velocity.length() > 1.0f) {
        float angle = std::atan2(velocity.y, velocity.x) * 180.0f / static_cast<float>(M_PI);
        shape.setRotation(angle + 90.0f);
    }
}