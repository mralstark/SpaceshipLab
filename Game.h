#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Spaceship.h"
#include "Asteroid.h"
#include "Nebula.h"

class Game {
private:
    sf::RenderWindow window;
    Spaceship ship;
    std::vector<Asteroid> asteroids;
    std::vector<Nebula> nebulas;
    
    sf::Clock clock;
    float speedMultiplier;
    
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
    static const int ASTEROID_COUNT = 7;
    static const int NEBULA_COUNT = 4;
    
    std::random_device rd;
    std::mt19937 gen;
    
public:
    Game();
    
    void run();
    
private:
    
    void initializeObjects();
    
    void handleEvents();
    
    void update();
    
    void render();
    
    void generateAsteroids();
    
    void generateNebulas();
};

#endif