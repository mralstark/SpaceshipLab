#include "Game.h"
#include <iostream>

Game::Game() 
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Космический корабль"),
      ship(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, WINDOW_WIDTH, WINDOW_HEIGHT),
      speedMultiplier(1.0f),
      gen(rd()) {
    
    window.setFramerateLimit(60);
    initializeObjects();
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::initializeObjects() {
    generateAsteroids();
    generateNebulas();
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0) {
                speedMultiplier += 0.2f;
            } else {
                speedMultiplier -= 0.2f;
            }
            
            if (speedMultiplier < 0.2f) speedMultiplier = 0.2f;
            if (speedMultiplier > 3.0f) speedMultiplier = 3.0f;
        }
        
        
        if (event.type == sf::Event::KeyPressed) { //рестарт
            if (event.key.code == sf::Keyboard::R) {
                initializeObjects(); 
            }
        }
    }
}

void Game::update() {
    float deltaTime = clock.restart().asSeconds();
    
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    
    float originalMaxSpeed = ship.getMaxSpeed();
    float originalAcceleration = ship.getAcceleration();
    
    ship.setMaxSpeed(originalMaxSpeed * speedMultiplier);
    ship.setAcceleration(originalAcceleration * speedMultiplier);
    
    ship.update(deltaTime, mousePosition, asteroids, nebulas);
    
    ship.setMaxSpeed(originalMaxSpeed);
    ship.setAcceleration(originalAcceleration);
}

void Game::render() {
    window.clear(sf::Color::Black);
    
    for (const auto& nebula : nebulas) {
        nebula.draw(window);
    }
    
    for (const auto& asteroid : asteroids) {
        asteroid.draw(window); 
    }
    
    ship.draw(window);
    
    window.display();
}

void Game::generateAsteroids() {
    std::uniform_real_distribution<float> posX(80.0f, WINDOW_WIDTH - 80.0f);
    std::uniform_real_distribution<float> posY(80.0f, WINDOW_HEIGHT - 80.0f);
    std::uniform_real_distribution<float> gravityRange(100.0f, 400.0f); 
    std::uniform_real_distribution<float> radiusRange(25.0f, 60.0f);    
    
    asteroids.clear();
    for (int i = 0; i < ASTEROID_COUNT; ++i) {
        float x, y;
        bool validPosition;
        int attempts = 0;
        
        do {
            x = posX(gen);
            y = posY(gen);
            
            Vector2 centerPos(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
            Vector2 asteroidPos(x, y);
            float distanceToCenter = Vector2::distance(centerPos, asteroidPos);
            
            validPosition = distanceToCenter > 100.0f; 
            attempts++;
        } while (!validPosition && attempts < 50);
        
        float radius = radiusRange(gen);
        float gravity = gravityRange(gen);
        
        asteroids.emplace_back(x, y, radius, gravity);
    }
}

void Game::generateNebulas() {
    std::uniform_real_distribution<float> posX(80.0f, WINDOW_WIDTH - 80.0f);
    std::uniform_real_distribution<float> posY(80.0f, WINDOW_HEIGHT - 80.0f);
    std::uniform_real_distribution<float> radiusRange(60.0f, 100.0f); 
    
    nebulas.clear();
    for (int i = 0; i < NEBULA_COUNT; ++i) {
        float x = posX(gen);
        float y = posY(gen);
        float radius = radiusRange(gen);
        float slowdown = 0.8f; 
        
        nebulas.emplace_back(x, y, radius, slowdown);
    }
}