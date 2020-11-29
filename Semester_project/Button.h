#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Button : public Drawable, public Transformable {
private:
	string TextOrPath;
	Text InnerText;
	Texture texture;
	Sprite InnerIcon;
	Font font;
	Color color;
	RectangleShape rectangle;
	Event* event;
	RenderWindow* Window;
	bool hided;

	Text lool;

	virtual void draw(RenderTarget& target, RenderStates states) const {
		target.draw(rectangle, states);
		if (!hided)
			(TextOrPath[0] == '.') ? target.draw(InnerIcon, states) : target.draw(InnerText, states);
	}
public:

	Button(string textOrPath, Color col, Event* ev, RenderWindow* window) : color(col), TextOrPath(textOrPath), event(ev), Window(window) {
		if (TextOrPath[0] == '.') {
			texture.loadFromFile(TextOrPath);
			InnerIcon.setTexture(texture);
			rectangle.setSize(Vector2f(InnerIcon.getGlobalBounds().width, InnerIcon.getGlobalBounds().height));
		}
		else {
			font.loadFromFile("./images/Templeton_Clean.ttf");
			InnerText = Text(textOrPath, font, 30);
			rectangle.setSize(Vector2f(InnerText.getGlobalBounds().width + 30, InnerText.getGlobalBounds().height + 15));
			InnerText.setOrigin(rectangle.getOrigin().x - 15, 0);
		}
		hided = false;
		lool = Text("Loool", font, 30);
		rectangle.setFillColor(color);
	}

	void replaceIcon(string path) {
		texture.loadFromFile(path);
		InnerIcon.setTexture(texture);
	}

	void setPos(float x, float y) {
		InnerIcon.setPosition(x, y);
		InnerText.setPosition(x, y);
		rectangle.setPosition(x, y);
	}

	void hide() {
		hided = true;
		rectangle.setFillColor(Color::Transparent);
		InnerText.setFillColor(Color::Transparent);
	}

	void unhide() {
		hided = false;
		rectangle.setFillColor(color);
		InnerText.setFillColor(Color::White);
	}

	bool isPressed() {
		if (!hided && (*event).type == Event::MouseButtonReleased && (*event).mouseButton.button == Mouse::Left && rectangle.getGlobalBounds().contains(Window->mapPixelToCoords(Mouse::getPosition(*Window)))) {
			return true;
		}
		return false;
	}

	void setEventPressed() {
		(*event).type = Event::MouseButtonPressed;
	}

	~Button() {}
};