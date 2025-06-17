#include "Medkit.h"

void Medkit::initMedkit()
{
	this->healbuffer.loadFromFile("medkitsound.mp3");
	this->healsound.setBuffer(this->healbuffer);
	this->healsound.setVolume(30.f);

	this->goofyheal.loadFromFile("nomedkit.mp3");
	this->healno.setBuffer(this->goofyheal);
	this->healno.setVolume(40.f);

	this->texture.loadFromFile("AIDKITv1.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(1.3, 1.3);
	this->sprite.setOrigin((this->texture.getSize().x / 2)*1.3, (this->texture.getSize().y / 2)*1.3);
}

void Medkit::initVariables()
{
	this->flySpeed = 4.f;
	this->healthRecive = 1;
}

Medkit::Medkit()
{
	this->initVariables();
	this->initMedkit();
}

void Medkit::fly()
{
	this->sprite.rotate(this->flySpeed);
	this->sprite.move(0, this->flySpeed);
}

void Medkit::playSound()
{
	this->healsound.play();
}

void Medkit::playSadSound()
{
	this->healno.play();
}

void Medkit::setPos(const sf::Vector2f& vect)
{
	this->sprite.setPosition(vect);
}

sf::Sprite Medkit::getShape()
{
	return this->sprite;
}

sf::FloatRect Medkit::getGlobalBounds()
{
	return this->sprite.getGlobalBounds();
}

int Medkit::getHealthRecive()
{
	return this->healthRecive;
}

int Medkit::heal()
{

	return this->getHealthRecive();
}
