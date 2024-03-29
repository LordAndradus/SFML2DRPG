#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height)
	: sprite(sprite), offsetX(offsetX), offsetY(offsetY)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offsetX, this->sprite.getPosition().y + offsetY);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(3.f);
	this->hitbox.setOutlineColor(sf::Color::Magenta);
}

HitboxComponent::~HitboxComponent()
{

}

bool HitboxComponent::checkIntersecting(const sf::FloatRect& fRect)
{
	return this->hitbox.getGlobalBounds().intersects(fRect);
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
