#include "MovementComponent.h"

//Using intializer list
MovementComponent::MovementComponent(sf::Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{

}

//Accessors
const sf::Vector2f & MovementComponent::getVelocity() const
{
	return this->velocity;
}

const bool MovementComponent::idle() const
{
	return this->velocity.x == 0.f && this->velocity.y == 0.f;
}

//Functions
void MovementComponent::move(const float& dt, const float dirX, const float dirY)
{
	//Acceleration
	this->velocity.x += this->acceleration * dirX;

	this->velocity.y += this->acceleration * dirY;
}

void MovementComponent::update(const float& dt)
{
	//Deceleration
	if (this->velocity.x > 0.f)
	{
		//Max Velocity Check Positive
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Deceleration x positive
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;

	}
	else if (this->velocity.x < 0.f)
	{
		//Max Velocity Check Positive
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}
	
	if (this->velocity.y > 0.f)
	{
		//Max Velocity Check Positive
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Deceleration y positive
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;

	}
	else if (this->velocity.y < 0.f)
	{
		//Max Velocity Check Positive
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Final movement
	this->sprite.move(this->velocity * dt); //Applies velocity to move

	static float time = 1;
	static float pile = 0;
	static bool printedScreen = false;

	pile += dt;

	if (pile >= time)
	{
		//system("cls");
		cout << "\x1b[A" << "\x1b[2K";
		printedScreen = false;
		pile -= time;
	}
	if (pile <= time && !printedScreen)
	{
		printedScreen = true;
		printf("Velocity: (%f, %f)\n", this->velocity.x, this->velocity.y);
	}
}
