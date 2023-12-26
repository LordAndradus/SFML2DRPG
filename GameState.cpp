#include "GameState.h"

void GameState::initKeybinds()
{
#define putMap(x, y) this->keybinds[x] = this->supportedKeys->at(y)
	putMap("MOVE_LEFT", "A");
	putMap("MOVE_RIGHT", "D");
	putMap("MOVE_UP", "W");
	putMap("MOVE_DOWN", "S");
#undef putMap
}

GameState::GameState(sf::RenderWindow* window, map<string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	this->initKeybinds();
}

GameState::~GameState()
{
	
}

void GameState::endState()
{
	printf("GateState is ending\n");
}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();

#define MOVE_PARAM(s) if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at(s))))
#define MOVE_COORD(x, y) this->player.move(dt, x, y)
	//Update player input
	MOVE_PARAM("MOVE_LEFT")
	{
		MOVE_COORD(-1.f, 0.f);
	}	
	
	MOVE_PARAM("MOVE_RIGHT")
	{
		MOVE_COORD(1.f, 0.f);
	}	
	
	MOVE_PARAM("MOVE_UP")
	{
		MOVE_COORD(0.f, -1.f);
	}	
	
	MOVE_PARAM("MOVE_DOWN")
	{
		MOVE_COORD(0.f, 1.f);
	}

#undef MOVE_PARAM
#undef MOVE_COORD
}

void GameState::update(const float& dt)
{
	this->updateInput(dt);
	
	this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;

	this->player.render(target);
}