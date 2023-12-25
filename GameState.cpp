#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
	: State(window)
{

}

GameState::~GameState()
{

}

void GameState::endState()
{
	printf("GateState is ending\n");
}

void GameState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void GameState::update(const float& dt)
{
	this->updateKeybinds(dt);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) printf("A\n");
}

void GameState::render(sf::RenderTarget* target)
{

}

#endif