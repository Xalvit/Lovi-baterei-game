#pragma once

#include "Menu.h"

enum PLAYER_ANIMS_STATES
{
	IDLE,
	MOVING_LEFT,
	MOVING_RIGHT,
	GOT_BATTERY
};

class Player
{
private:
	// variables

	short animState;
	bool animSwitch;
	bool moving;

	sf::RectangleShape staminaBar;
	sf::RectangleShape staminaBarAfter;

	sf::IntRect currentFrame;
	sf::Clock animTimer;
	float staminaRevive;
	float sprintGoing;
	float sprintSpeed;
	float stamina;
	float speed;
	float speedTemp;
	float jumpPower;
	float gravityPower;
	int health;
	int maxHealth;
	sf::Sprite player;

	sf::Texture playerTexture;
	sf::Sound footsteps;
	sf::SoundBuffer footstepsBuffer;

	sf::Sound batteryCollected;
	sf::SoundBuffer batteryCollectedBuffer;

	sf::Sound evilTouch;
	sf::SoundBuffer evilTouchBuffer;

	// functions
	void initVariables();
	void initSounds();
	void initPlayer();
	void updatePlayer();
public:
	// constr & destr
	Player();
	~Player();

	// accessors
	const bool& getAnimSwitch();
	int getHealth();
	//sf::Vector2f getSize();
	// functions
	void render(sf::RenderWindow& window);
	void setOrigin(const sf::Vector2f& vector2f);
	void crouch();
	void evilCrouch();
	sf::FloatRect getGlobalBounds();
	void setPosition(const sf::Vector2f& vector2f);
	void resetAnimTimer();
	sf::Sprite getPlayer();
	void update(sf::Event& ev);
	void updateAnimations(sf::Event& ev);
	int getMaxHealth();
	void setAnimStatus(const unsigned int& ANIM_SEE_ENUM);
	sf::Vector2f getPosition();
	// Player health -= number
	void setHealth(const unsigned short& number);
	// Player health = number STRING
	void footstepsStop();
	void updateSpeed(const float& dif);
	void setHealth(const std::string& charr);
	void eventsPoll(sf::Event& ev);
	void moveLeft();
	void moveRight();
	void sprint();
};

