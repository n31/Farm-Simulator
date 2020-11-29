#pragma once
#include <SFML/Graphics.hpp>
#include "Warehouse.h"
#include <string>
#include "VehicleSprite.h"
#include "Button.h"
#include "Market.h"
#include <iostream>
#include "CollisionMap.h"

using namespace std;
using namespace sf;

class HUD : public Transformable, public Drawable {
private:
    int Location;
    CollisionMap* Cmap;
    RenderWindow* Window;
    Event* event;
	Warehouse* Wh;
    VehicleSprite* Car;
    Font font;
    Text WheatText, CoinsText;
    RectangleShape StatsDiv;
    Market* market;
    Button* TestButton;
    Button* ExchangeButton;
    Texture FarmImage;
    Sprite FarmBackground;
    Button* bg;

    Button** FieldsOptionsArray;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(*bg, states);
        target.draw(StatsDiv, states);
        target.draw(WheatText, states);
        target.draw(CoinsText, states);
        target.draw(*TestButton, states);
        target.draw(*ExchangeButton, states);
        for (int i = 0; i < 8; i++) {
            target.draw(*FieldsOptionsArray[i], states);
        }
    }
public:
	HUD(Warehouse* wh, VehicleSprite* car, RenderWindow* window, Event* ev, Market* mark, CollisionMap* cmap) : Wh(wh), Car(car), Window(window), event(ev), market(mark), Cmap(cmap) {
        Car->setBlock(true);
        Location = 0;
        font.loadFromFile("./images/Templeton_Clean.ttf");
        WheatText = Text(to_string(Wh->getWheat()), font, 30);
        CoinsText = Text(to_string(Wh->getCoins()), font, 30);
        StatsDiv = RectangleShape(Vector2f(200, 100));
        StatsDiv.setFillColor(Color::Blue);
        //StatsDiv = RectangleShape(Vector2f(1376, 768));
        //StatsDiv.setFillColor(Color::Blue);

        FarmImage.loadFromFile("./images/farm.jpg");
        FarmBackground.setTexture(FarmImage);
        FarmBackground.setScale(0.2, 0.2);


        bg = new Button("./images/farm.jpg", Color::Transparent, event, window);
        //(*bg).setScale(0.2, 0.2);

        TestButton = new Button("./images/window_icon.png", Color::Transparent, event, window);
        ExchangeButton = new Button("./images/exchange.png", Color::Green, event, window);

        FieldsOptionsArray = new Button*[8];
        for (int i = 3; i <= 10; i++) {
            FieldsOptionsArray[i - 3] = new Button("Field " + to_string(i * 10) + 'x' + to_string(i * 10) + " " + to_string(i * 100) + '$', Color::Green, event, window);
        }

    }

    void update() {
        // update the position of the HUD
        setPosition(Car->getPosition());

        // update and move wheat text according the HUD position
        WheatText.setString(to_string((int)Wh->getWheat()) + " kg");
        WheatText.setPosition(getPosition().x - 668, getPosition().y - 334);

        // update and move wheat text according the HUD position
        CoinsText.setString('$' + to_string((int)Wh->getCoins()));
        CoinsText.setPosition(getPosition().x - 668, getPosition().y - 374);

        // move StatsDiv according the HUD position;
        StatsDiv.setPosition(getPosition().x - 688, getPosition().y -384);

        // move HomeButton according the HUD position;
        (*TestButton).setPos(getPosition().x + 588, getPosition().y + 284);

        // move ExchangeButton according the HUD position;
        (*ExchangeButton).setPos(getPosition().x - 488, getPosition().y - 384);

        (*bg).setPos(getPosition().x - 688, getPosition().y - 384);

        for (int i = 0; i < 8; i++) {
            (*FieldsOptionsArray[i]).setPos(getPosition().x - 588, getPosition().y - 184 + (i * 50));
        }


        // check the Location
        if (Location == 0) {
            (*ExchangeButton).unhide();
            (*bg).unhide();
            (*TestButton).replaceIcon("./images/grain_icon.png");
            for (int i = 0; i < 8; i++) {
                (*FieldsOptionsArray[i]).unhide();
            }

            for (int i = 0; i < 8; i++) {
                if ((*FieldsOptionsArray[i]).isPressed()) {
                    int fieldSize = (i + 3) * 10;
                    if ((*market).buyField(fieldSize)) {
                        (*Cmap).createNewSize(fieldSize);
                        (*Car).respawn();

                    }
                    (*FieldsOptionsArray[i]).setEventPressed();
                }
            }
        }
        else if (Location == 1) {
            (*ExchangeButton).hide();
            (*bg).hide();
            (*TestButton).replaceIcon("./images/window_icon.png");
            for (int i = 0; i < 8; i++) {
                (*FieldsOptionsArray[i]).hide();
            }
        }

        if ((*TestButton).isPressed()) {
            Location = !Location;
            Car->setBlock(!Car->getBlock());
            (*TestButton).setEventPressed();
        }

        if ((*ExchangeButton).isPressed()) {
            (*market).sellWheat();
            (*ExchangeButton).setEventPressed();
        }
        
        

        
    }

	~HUD() {}
};