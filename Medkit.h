#pragma once

#include "Menu.h"

class Medkit
{
private:
	float flySpeed;
	int healthRecive;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::SoundBuffer goofyheal;
	sf::Sound healno;
	sf::SoundBuffer healbuffer;
	sf::Sound healsound;
	void initMedkit();
	void initVariables();
public:
	Medkit();

	void fly();
	void playSound();
	void playSadSound();
	void setPos(const sf::Vector2f& vect);
	sf::Sprite getShape();
	sf::FloatRect getGlobalBounds();
	int getHealthRecive();
	int heal();
};

