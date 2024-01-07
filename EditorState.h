#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Button.h"

class EditorState :
    public State
{
public:
    EditorState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& dt);
    void update(const float& dt);
    void updateButtons();
    void render(sf::RenderTarget* target = nullptr);
    void renderButtons(sf::RenderTarget& target);

protected:

private:
    //Variables
    sf::Font font;

    map<string, Button*> buttons;

    //Initializer
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
};

#endif