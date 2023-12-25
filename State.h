#ifndef STATE_H
#define STATE_H

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

class State
{
public:
	//Constructor/Destructor
	State(sf::RenderWindow* window);
	virtual ~State();

	virtual void endState() = 0;

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

private:
	sf::RenderWindow* window;
	vector<sf::Texture*> textures;
};

#endif