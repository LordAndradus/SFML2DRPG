#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"

using namespace std;

class Entity
{
public:
	Entity();
	virtual ~Entity();

	//Component Functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& textureSheet);

	//Core Functions
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt, const float x, const float y);

protected:
	sf::Sprite sprite;
	
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

private:
	void initVariables();
};

#endif