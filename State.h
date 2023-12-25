#ifndef STATE_H
#define STATE_H

#include "Entity.h"

using namespace std;

class State
{
public:
	//Constructor/Destructor
	State(sf::RenderWindow* window);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();
	
	virtual void endState() = 0;
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
	sf::RenderWindow* window;
	vector<sf::Texture*> textures;
	bool quit;

private:
};

#endif