#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"

class MainMenuState :
    public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    map<string, Button*> buttons;

    //Initializer
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~MainMenuState();

    //Functions
    void updateInput(const float& dt);
    void update(const float& dt);
    void updateButtons();
    void render(sf::RenderTarget* target = nullptr);
    void renderButtons(sf::RenderTarget* target = nullptr);
};

#endif