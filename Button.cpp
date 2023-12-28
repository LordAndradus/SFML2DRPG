#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font,
	string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = IDLE;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	
	this->font = font; 
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(24);
	this->text.setPosition(
		this->shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

//Accessors
const bool Button::isActive() const
{
	return buttonState == ACTIVE;
}

//Functions
void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

void Button::update(const sf::Vector2f mousePos)
{
	this->buttonState = IDLE;

	//Checks if there is a collision between the mouse and button
	//Basically just hovering
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = HOVER;

		//If the button is clicked
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = ACTIVE;
		}
	}

	switch (buttonState)
	{
	case IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}
