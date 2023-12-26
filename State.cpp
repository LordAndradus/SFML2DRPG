#include "State.h"

State::State(sf::RenderWindow* window, map<string, int>* supportedKeys)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->quit = false;
}

State::~State()
{

}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::checkForQuit()
{
	this->quit = sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("QUIT")));
}
