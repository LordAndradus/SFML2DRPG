#ifndef STATE_H
#define STATE_H

#include "Entity.h"

#include <shlobj.h>
#include <shlwapi.h>

class State
{
public:
	//Constructor/Destructor
	State(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();
	
	virtual void endState() = 0;
	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
	stack<State*>* states; //Points to a stack full of state classes
	sf::RenderWindow* window;
	map<string, int>* supportedKeys;
	map<string, int> keybinds;

	bool quit;

	sf::Vector2i mousePosScreen; //Follows the mouse even when it exits the window. Strictly on the monitor
	sf::Vector2i mousePosWindow; //Within the window. Cannot track it when it exits the window
	sf::Vector2f mousePosView; //Tracks the camera in the game world. It can far exceed the screen position.

	//Resources
	vector<sf::Texture*> textures;

	virtual void initKeybinds() = 0;
private:
};

#endif