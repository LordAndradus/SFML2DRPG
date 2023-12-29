#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <stdio.h>
#include <iostream>
#include <map>

#include <SFML\Network.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>

using namespace std;

class AnimationComponent
{
public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	//Functions
	void addAnimation(const string key, float animationTimer, 
		int startFrameX, int startFrameY, int framesX, int framesY, 
		int width, int height);

	/*void startAnimation(const string animation);
	void pauseAnimation(const string animation);
	void resetAnimation(const string animation);*/

	void play(const float& dt, const string key);

protected:

private:
	class Animation
	{
	public:
		//Variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		int width, height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		//Constructer/Destructor
		Animation(sf::Sprite& sprite, sf::Texture& textureSheet, float animationTimer, int startFrameX, int startFrameY, int framesX, int framesY, int width, int height)
			: sprite(sprite), textureSheet(textureSheet), animationTimer(animationTimer), width(width), height(height)
		{
			this->timer = 0.f;

			this->startRect = sf::IntRect(startFrameX * width, startFrameY * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(framesX * width, framesY * height, width, height);
			
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		//Functions
		void play(const float& dt)
		{
			//Update timer
			this->timer += 100.f * dt;

			if (this->timer >= this->animationTimer)
			{
				this->timer = 0.f;

				if (this->currentRect.left < this->endRect.left)
				{
					this->currentRect.left += this->width;
				}
				else
				{
					this->currentRect.left = this->startRect.left;
				}
			}

			this->sprite.setTextureRect(this->currentRect);
		}

		void reset()
		{
			this->timer = 0.f;
			this->currentRect = this->startRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	map<string, Animation*> animations;
	Animation* lastAnimation;
};

#endif