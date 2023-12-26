#include "Entity.h"

Entity::Entity()
{
	this->shape.setSize(sf::Vector2f(50.0f, 50.0f));
	this->shape.setFillColor(sf::Color::White);
	this->movementSpeed = 500.0f;
	this->shape.setPosition(sf::Vector2f((float)1920 / 2, (float)1080 / 2));
}

Entity::~Entity()
{

}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Entity::move(const float &dt, const float dir_x, const float dir_y)
{
#define multiplier this->movementSpeed * dt
	this->shape.move(dir_x * multiplier, dir_y * multiplier);
#undef multiplier
}
