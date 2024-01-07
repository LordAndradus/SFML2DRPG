#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include <iostream>
#include <ctime>
#include <cstdlib>


#include <SFML\Network.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>

class HitboxComponent
{
private:
	sf::Sprite& sprite; //Requires a reference to a sprite
	sf::RectangleShape hitbox;
	float offsetX, offsetY;

protected:

public:
	HitboxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height);
	virtual ~HitboxComponent();

	//Functions
	bool checkIntersecting(const sf::FloatRect& fRect);
	void update();
	void render(sf::RenderTarget& target);
};

#endif