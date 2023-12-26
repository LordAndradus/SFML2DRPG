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

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

	virtual void move(const float& dt, const float x, const float y);

protected:
	sf::RectangleShape shape;
	map<string, int> *supportedKeys;
	float movementSpeed;

private:

};

#endif