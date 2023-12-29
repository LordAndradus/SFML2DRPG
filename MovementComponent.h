#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

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

class MovementComponent
{
public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelocity() const;

	//Functions
	const bool idle() const;

	void move(const float& dt, const float dirX, const float dirY);
	void update(const float& dt);

protected:

private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	//Initializers
	

};

#endif