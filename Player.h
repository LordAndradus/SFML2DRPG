#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
class Player :
    public Entity
{
public:
    Player(float x, float y, sf::Texture* texture);
    virtual ~Player();

    //Variables

    //Initializer Functions
    void initVariables();
    void initComponents();

protected:

private:

};

#endif