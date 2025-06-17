#include "Battery.h"

// functions private
void Battery::initVariables()
{
	this->batteryType = BASIC;
	this->cought = false;
	this->batteryCosts = 10;
	this->flySpeed = 5.f;
	//this->flyTemp = this->flySpeed;
}

void Battery::loadTexture()
{
	if (!this->batteryTexture.loadFromFile("batareya.png"))
	{
		throw "batareya.png NOT FOUND";
	}
	else
	{
		this->batteryTexture.loadFromFile("batareya.png");
		this->battery.setTexture(this->batteryTexture);
	}
		
}

void Battery::loadEvilTexture()
{
	if (!this->batteryTexture.loadFromFile("danger_batareya.png"))
	{
		throw "danger_batareya.png NOT FOUND";
	}
	else
	{
		this->batteryTexture.loadFromFile("danger_batareya.png");
		this->battery.setTexture(this->batteryTexture);
	}
}

void Battery::initBattery()
{
	this->battery.setScale(0.225, 0.225);
	this->battery.setOrigin(
		sf::Vector2f(
			this->batteryTexture.getSize().x / 2,
			this->batteryTexture.getSize().y / 2
		)
	);
}




// constr & destr
Battery::Battery()
{
	this->loadTexture();
	this->initVariables();
	this->initBattery();
	this->basicTypeBattery();

}

Battery::Battery(const unsigned short num)
{
	this->loadEvilTexture();
	this->initVariables();
	this->initBattery();
	this->basicTypeBattery();

}

Battery::~Battery(){}

// functions public
void Battery::render(sf::RenderWindow& window)
{
	window.draw(this->battery);
}

void Battery::update()
{
	this->flyBattery();
}

void Battery::basicTypeBattery()
{
	switch (this->batteryType)
	{
	case BASIC:
	{
		// All basic things in "void initBattery()"
		break;
	}
	case BIG:
	{
		this->batteryType = BIG;
		this->battery.scale(2, 2);
		this->battery.setOrigin(sf::Vector2f(
			(this->batteryTexture.getSize().x / 4.45) / 2,
			(this->batteryTexture.getSize().y / 4.45) / 2));
		this->flySpeed = floor(this->flySpeed / 1.7);
		this->batteryCosts /= 2;
		break;
	}
	case SMALL:
	{
		this->batteryType = SMALL;
		this->battery.scale(0.5, 0.5);
		this->battery.setOrigin(sf::Vector2f(
			(this->batteryTexture.getSize().x / 4.45) / 0.5,
			(this->batteryTexture.getSize().y / 4.45) / 0.5));
		this->flySpeed = floor(this->flySpeed * 1.7);
		this->batteryCosts *= 2;
		break;
	}
	case SLIM:
	{
		this->batteryType = SLIM;
		this->battery.scale(0.5, 1);
		this->battery.setOrigin(sf::Vector2f(
			(this->batteryTexture.getSize().x / 4.45) / 0.5,
			(this->batteryTexture.getSize().y / 4.45) / 1));
		this->flySpeed = floor(this->flySpeed * 1.2);
		this->batteryCosts *= 1.2;
		break;
	}
	case FAT:
	{
		this->batteryType = FAT;
		this->battery.scale(1.8, 1);
		this->battery.setOrigin(sf::Vector2f(
			(this->batteryTexture.getSize().x / 4.45) / 1.8,
			(this->batteryTexture.getSize().y / 4.45) / 1));
		this->flySpeed = floor(this->flySpeed / 1.5);
		this->batteryCosts /= 1.5;
		break;
	}
	default:
		break;
	}
}

void Battery::setTexture(const std::string& filename)
{
	sf::Texture textur;
	textur.loadFromFile(filename);
	this->battery.setTexture(textur);
}

void Battery::flyBattery()
{
	this->battery.rotate(this->flySpeed);
	this->battery.move(0,this->flySpeed);
}


void Battery::flyBattery(const unsigned short a)
{
	this->battery.rotate(this->flySpeed + (this->flySpeed/a));
	this->battery.move(0, this->flySpeed + (this->flySpeed /a));
}

void Battery::setCought(const bool& iscought)
{
	this->cought = iscought;
}

void Battery::setPos(const sf::Vector2f& vector2f)
{
	this->battery.setPosition(vector2f);
}

void Battery::setSize(sf::Vector2f& vector2f)
{
	this->battery.setScale(vector2f);
}

// accessor

int Battery::getBatteryCost() const
{
	return this->batteryCosts;
}

sf::Sprite Battery::getShape()
{
	return this->battery;
}

sf::Vector2f Battery::getPosition()
{
	return sf::Vector2f(this->battery.getPosition());
}

sf::FloatRect Battery::getGlobalBounds()
{
	return this->battery.getGlobalBounds();
}

//
//
// GOOFY BATTERY
//
//

void GoofyBattery::initSprite()
{
	this->evilBatteryTexture.loadFromFile("danger_batareya.png");
	this->evilBattery.setTexture(this->evilBatteryTexture);

	this->boomTexture.loadFromFile("explotano.png");
	this->boomEffect.setTexture(&this->boomTexture);
	this->boomEffect.setSize(sf::Vector2f(200.f,200.f));
}

void GoofyBattery::loadCheck()
{
	if (!this->evilBatteryTexture.loadFromFile("danger_batareya.png"))
		throw "danger_batareya.png NOT FOUND";

	if (!this->boomTexture.loadFromFile("explotano.png"))
		throw "explotano.png NOT FOUND";
}


GoofyBattery::GoofyBattery() : Battery(1)
{
	this->loadCheck();
	this->initSprite();
	this->basicTypeBattery();
}

GoofyBattery::~GoofyBattery(){}

void GoofyBattery::basicTypeBattery()
{
	this->evilBattery.setScale(1,1);//0.225, 0.225);
	this->evilBattery.setOrigin(
		sf::Vector2f(
			this->evilBatteryTexture.getSize().x / 2,
			this->evilBatteryTexture.getSize().y / 2
		)
	);
}

void GoofyBattery::kaboom()
{
	this->boomEffect.setPosition(sf::Vector2f(
		this->evilBattery.getPosition().x,this->evilBattery.getPosition().y));
}

void GoofyBattery::setPosBom(sf::Vector2f vec)
{
	this->boomEffect.setPosition(vec);
}


sf::RectangleShape GoofyBattery::bomShape()
{
	return this->boomEffect;
}
