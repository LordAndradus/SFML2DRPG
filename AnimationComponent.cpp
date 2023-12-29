#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	: sprite(sprite), textureSheet(textureSheet)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto i : this->animations) delete i.second;
}

void AnimationComponent::addAnimation(const string key, float animationTimer,
	int startFrameX, int startFrameY, int framesX, int framesY,
	int width, int height)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet,
		animationTimer, startFrameX, 
		startFrameY, framesX, framesY, width, height
	);
}

//Function bois


void AnimationComponent::play(const float& dt, const string key)
{
	this->animations[key]->play(dt);
}
