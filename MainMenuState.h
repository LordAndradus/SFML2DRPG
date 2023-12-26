#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"

class MainMenuState :
    public State
{
private:
    //Variables
    sf::RectangleShape background;

    //Initializer
    void initKeybinds();

public:
    MainMenuState(sf::RenderWindow* window, map<string, int>* supportedKeys);
    virtual ~MainMenuState();

    //Functions
    void endState();
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

#endif