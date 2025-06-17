#pragma once

#include "Player.h"

enum BATTERY_TYPE_SIZE
{
	BASIC = 1,
	BIG,
	SMALL,
	SLIM,
	FAT
};

class Battery
{
private:
	// variables
	bool cought;
	int batteryCosts;
	sf::Sprite battery;
	sf::Texture batteryTexture;
	int batteryType;
	float flySpeed;
	//float flyTemp;

	// functions
	void initVariables();
	void loadTexture();
	void loadEvilTexture();
	void initBattery();
public:
	// constr & destr
	Battery();
	Battery(const unsigned short num);
	~Battery();

	// functions
	void render(sf::RenderWindow& window);
	void update();
	void virtual basicTypeBattery();
	void setTexture(const std::string& filename);
	void flyBattery();
	/* Optimal a = 2, cuz  flyspeed = flyspeed+ (flyspeed/a)*/
	void flyBattery(const unsigned short a);
	void setCought(const bool& iscought);
	void setPos(const sf::Vector2f& vector2f);
	void setSize(sf::Vector2f& vector2f);

	// accessor
	int getBatteryCost() const;
	sf::Sprite getShape();
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
};

//
// 
// GOOFY BATTERY
//
//

class GoofyBattery : public Battery
{
private:
	sf::Sprite evilBattery;
	sf::Texture evilBatteryTexture;

	sf::RectangleShape boomEffect;
	sf::Texture boomTexture;


	void initSprite();
	void loadCheck();


public:
	GoofyBattery();
	~GoofyBattery();

	void basicTypeBattery() override;
	void kaboom();
	void setPosBom(sf::Vector2f vec);
	sf::RectangleShape bomShape();
};