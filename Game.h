#ifndef GAME_H
#define GAME_H

#include "GameState.h"

using namespace std;

class Game
{
public:
	//Constructor/Destructor
	Game();
	virtual ~Game();

	bool DEBUG_MODE = 0;

	//Game Loop
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();

private:
	//Hidden variables
	sf::RenderWindow *window;
	sf::Event sfEvent;

	//Frame rendering variables
	sf::Clock dtClock;
	double dt;

	stack<State*> states;

	//Initializers
	void initGameWindow();
	void initStates();
	bool loadWindowINI();
};

#endif