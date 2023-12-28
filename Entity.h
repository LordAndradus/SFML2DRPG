#ifndef ENTITY_H
#define ENTITY_H

#define NOMINMAX
#include <Windows.h>
#include <filesystem>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

#include <stack>
#include <map>

#include <SFML\Network.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>

using namespace std;

class Entity
{
public:
	Entity();
	virtual ~Entity();

	//Component Functions
	void createSprite(sf::Texture* texture);

	//Core Functions
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt, const float x, const float y);

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;
	float movementSpeed;

private:
	void initVariables();
};

#endif