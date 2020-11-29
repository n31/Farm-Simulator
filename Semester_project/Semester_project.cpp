#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include "TileMap.h"
#include "VehicleSprite.h"
#include "CollisionMap.h"
#include "LevelMap.h"
#include "Market.h"
#include "Warehouse.h"
#include "HUD.h"

#define _WIN32_WINNT 0x0500
#include <windows.h>

using namespace sf;
using namespace std;

bool intersect(CircleShape cell, Vector2f shape) {
    int xFrom = cell.getPosition().x - cell.getRadius();
    int xTo = cell.getPosition().x + cell.getRadius();
    int yFrom = cell.getPosition().y - cell.getRadius();
    int yTo = cell.getPosition().y + cell.getRadius();
    int x = shape.x;
    int y = shape.y;
    if ((x >= xFrom && x <= xTo) && (y >= yFrom && y <= yTo)) return true;
    else return false;
}

sf::Vector2f inverseVec(sf::Vector2f v) {
    v.x *= -1;
    v.y *= -1;
    return v;
}



int main()
{
    sf::Image icon;
    icon.loadFromFile("./images/window_icon.png");
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    RenderWindow window(VideoMode(1376, 768), "Farm Simulator", sf::Style::Titlebar | sf::Style::Close);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    Warehouse warehouse;
    Market market(&warehouse);
    CollisionMap cmap;
    cmap.createNewSize(30);
    LevelMap lmap("./images/tilemap.png", &cmap);
    VehicleSprite car(3.5f, "./images/resized.png", &cmap, &warehouse);
    View view(car.getPosition(), Vector2f(1376.f, 768.f));

    CollisionMap cBgMap;
    cBgMap.createBlank(100 + 45, 1);
    LevelMap BgMap("./images/tilemap.png", &cBgMap);
    BgMap.setPosition(-688-32, -384-32);

    Event event;
    HUD hud(&warehouse, &car, &window, &event, &market, &cmap);
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        hud.update();
        car.checkCollision();
        lmap.update();
        view.setCenter(car.getPosition());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            car.moveForward();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            car.moveBackwards();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            car.rorateRight();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            car.rorateLeft();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            car.rorateLeft();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            car.rorateRight();
        }
        

        window.clear();
        
        window.setView(view);
        window.draw(BgMap);
        window.draw(lmap);
        window.draw(car);
        window.draw(hud);
        window.display();
    }

    return 0;
}