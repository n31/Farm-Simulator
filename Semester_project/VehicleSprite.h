#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <CollisionMap.h>
#include "Warehouse.h"

using namespace sf;
using namespace std;

class VehicleSprite : public Sprite {
private:
    bool Block;
    Vector2f Direction;
    float Speed;
    Texture Skin;
    CollisionMap* collMap;
    Warehouse* Wh;
protected:
    sf::Vector2f adjVec(float rotation, float speed) {
        int section = 0;
        while (rotation >= 0) {
            section++;
            rotation -= 90.f;
        }
        rotation += 90.f;

        float part = speed / 90;
        float adjSpeed = rotation * part;
        float anoSpeed = speed - adjSpeed;

        float x, y;
        if (section == 1) {
            x = 1 * adjSpeed;
            y = -1 * anoSpeed;
        }
        else if (section == 2) {
            x = 1 * anoSpeed;
            y = 1 * adjSpeed;
        }
        else if (section == 3) {
            x = -1 * adjSpeed;
            y = 1 * anoSpeed;
        }
        else {
            x = -1 * anoSpeed;
            y = -1 * adjSpeed;
        }

        return sf::Vector2f(x, y);
    }

    sf::Vector2f inverseVec(sf::Vector2f v) {
        v.x *= -1;
        v.y *= -1;
        return v;
    }
public:
    VehicleSprite(float speed, string texturePath, CollisionMap* collmap) : Speed(speed), collMap(collmap) {
        this->Wh = Warehouse::GetInstance();
        this->Block = false;
        Texture texture;
        if (!texture.loadFromFile(texturePath)) {
            cout << "[!] Can't open VehicleSprite texture (" << texturePath << ")\n";
        }
        texture.setSmooth(true);
        this->Skin = texture;
        setTexture(Skin);
        setOrigin(Skin.getSize().x / 2, Skin.getSize().y * 0.8);
        //setPosition(200, 200);
        respawn();
    }

    Vector2f getDirections() { return Direction; }

    void setBlock(bool f) { Block = f; }
    bool getBlock() { return Block; }

    void checkCollision() {
        float carTop = getGlobalBounds().top;
        float carBottom = carTop + getGlobalBounds().height;
        float carLeft = getGlobalBounds().left;
        float carRight = getGlobalBounds().width + carLeft;

        // find jMin
        int jMin = 0;
        if (carLeft < 0) jMin = 1;
        for (int jMinBounds = 0; jMinBounds < carLeft && jMin < collMap->getCols(); jMin++, jMinBounds += 32);
        // find jMax
        int jMax = 0;
        if (carLeft < 0 && carRight < 0) jMax = 1;
        for (int jMaxBounds = 0; jMaxBounds < carRight && jMax < collMap->getCols(); jMax++, jMaxBounds += 32);
        // find iMin
        int iMin = 0;
        if (carTop < 0) iMin = 1;
        for (int iMinBounds = 0; iMinBounds < carTop && iMin < collMap->getRows(); iMin++, iMinBounds += 32);
        // find iMax
        int iMax = 0;
        if (carTop < 0 && carBottom < 0) iMax = 1;
        for (int iMaxBounds = 0; iMaxBounds < carBottom && iMax < collMap->getRows(); iMax++, iMaxBounds += 32);
        
        // replace map tiles
        for (int i = iMin - 1; i <= iMax - 1; i++) {
            for (int j = jMin - 1; j <= jMax - 1; j++) {
                if (collMap->getElem(i, j) == 3) {
                    move(inverseVec(getDirections()));
                    

                    if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S)) {
                        rorateRight();
                    }
                    if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S)) {
                        rorateLeft();
                    }
                }
                else if (collMap->getElem(i,j) == 2) {
                    collMap->updateElem(i, j, 0);
                    Wh->incrWheat();
                }
            }
        }
    }

    void moveForward() {
        if (!Block) {
            Direction = adjVec(getRotation(), Speed);
            move(Direction);
        }
    }

    void moveBackwards() {
        if (!Block) {
            Direction = inverseVec(adjVec(getRotation(), Speed));
            move(Direction);
        }
    }

    void rorateRight() {
        float r = getRotation();
        r += 0.75f;
        if (!Block) setRotation(r);
    }

    void rorateLeft() {
        float r = getRotation();
        r -= 0.75f;
        if (!Block) setRotation(r);
    }

    void respawn() {
        setRotation(0);
        setPosition(32 + 48, (*collMap).getCols() * 32 - 32 - 48);
    }

};