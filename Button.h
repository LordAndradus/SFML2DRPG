#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML\Network.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>

using namespace std;

enum state {
	IDLE = 0,
	HOVER,
	ACTIVE
};

class Button
{
public:
	Button(float x, float y, float width, float height, sf::Font* font, 
	string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	//Accessors
	const bool isActive() const;

	//Functions
	void render(sf::RenderTarget* target);
	void update(const sf::Vector2f mousePos);

protected:

private:
	unsigned short buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
};

#endif