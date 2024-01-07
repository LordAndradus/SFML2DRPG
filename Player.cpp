#include "Player.h"

//Constructor & Destructor
Player::Player(float x, float y, sf::Texture& textureSheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 0, 0, (474/4), 172);
	this->createMovementComponent(500.0f, 10.f, 4.f);
	this->createAnimationComponent(textureSheet);

	this->animationComponent->addAnimation("IDLE_RIGHT", 25.f, 0, 0, 3, 0, (474/4), 172);
	this->animationComponent->addAnimation("RUN_RIGHT", 13.f, 0, 1, 6, 1, (1299 / 7), 172);
}

Player::~Player()
{

}

//Initializer functions
void Player::initVariables()
{

}

void Player::initComponents()
{

}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	if (this->movementComponent->idle()) this->animationComponent->play(dt, "IDLE_RIGHT");
	else this->animationComponent->play(dt, "RUN_RIGHT");

	this->hitboxComponent->update();
}
