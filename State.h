#ifndef STATE_H
#define STATE_H

#include "Entity.h"

class State
{
public:
	//Constructor/Destructor
	State(sf::RenderWindow* window, map<string, int>* supportedKeys);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();
	
	virtual void endState() = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
	sf::RenderWindow* window;
	map<string, int>* supportedKeys;
	map<string, int> keybinds;

	bool quit;

	//Resources
	vector<sf::Texture*> textures;

	virtual void initKeybinds() = 0;
private:
};

#endif