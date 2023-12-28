#include "Entity.h"

void Entity::initVariables()
{
	this->texture = nullptr;
	this->sprite = nullptr;
	this->movementSpeed = 500.0f;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->sprite;
}

//Component Functions
void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);
}


//Core Functions
void Entity::update(const float& dt)
{
	static float time = 1;
	static float pile = 0;
	static bool printedScreen = false;

	pile += dt;

	if (pile >= time)
	{
		//system("cls");
		cout << "\x1b[A";
		cout << "\x1b[2K";
		printedScreen = false;
		pile -= time;
	}
	if (pile <= time && !printedScreen)
	{
		printedScreen = true;
		printf("Player coord: (%f, %f)\n", this->sprite->getPosition().x, this->sprite->getPosition().y);
	}
}

void Entity::render(sf::RenderTarget* target)
{
	if (this->sprite) target->draw(*this->sprite);
}

void Entity::setPosition(const float x, const float y)
{
	if (this->sprite)
		this->sprite->setPosition(x, y);
}

void Entity::move(const float &dt, const float dir_x, const float dir_y)
{
#define multiplier this->movementSpeed * dt
	if(this->sprite)
		this->sprite->move(dir_x * multiplier, dir_y * multiplier);
#undef multiplier
}
