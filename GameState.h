#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState :
    public State
{
private:
    Player* player;
    
    //Initializers
    void initKeybinds();
    void initTextures();
    void initPlayer();

public:
    GameState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~GameState();

    //Functions
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

#endif