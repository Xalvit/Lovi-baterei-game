#include "Player.h"

// private functions
void Player::initVariables()
{
	this->moving = false;
	this->staminaRevive = 0.2f;
	this->stamina = 100.f;
	this->sprintSpeed = 4.f;
	this->health = 10;
	this->maxHealth = this->health;
	this->speed = 15.f;
	this->speedTemp = this->speed;
	this->sprintGoing = this->speed + this->sprintSpeed;
	this->gravityPower = 1.f;
	this->jumpPower = (10.f + this->gravityPower);

	this->playerTexture.loadFromFile("BatteryPlrAnimations.png");

	this->animTimer.restart();
	this->animState = IDLE;
	this->animSwitch = true;

	this->staminaBar.setSize(sf::Vector2f(10*this->stamina,65));
	this->staminaBar.setPosition(sf::Vector2f(
	400,
	sf::VideoMode::getDesktopMode().height - 80));
	this->staminaBar.setFillColor(sf::Color::Cyan);

	this->staminaBarAfter.setSize(this->staminaBar.getSize());
	this->staminaBarAfter.setPosition(this->staminaBar.getPosition());
	this->staminaBarAfter.setFillColor(sf::Color(100,100,100));
}

void Player::initSounds()
{
	if (!this->footstepsBuffer.loadFromFile("footsteps.mp3"))
	{
		throw "footsteps.mp3 NOT FOUND";
	}
	else
	{ 
		this->footstepsBuffer.loadFromFile("footsteps.mp3");
		this->footsteps.setBuffer(this->footstepsBuffer);
		this->footsteps.setLoop(true);
		this->footsteps.setVolume(50.f);
	}


	if (!this->batteryCollectedBuffer.loadFromFile("CollectedBattery.mp3"))
	{
		throw "CollectedBattery.mp3 NOT FOUND";
	}
	else
	{
		this->batteryCollectedBuffer.loadFromFile("CollectedBattery.mp3");
		this->batteryCollected.setBuffer(this->batteryCollectedBuffer);
	}
	if (!this->evilTouchBuffer.loadFromFile("painBattery.mp3"))
	{
		throw "painBattery.mp3 NOT FOUND";
	}
	else
	{
		this->evilTouchBuffer.loadFromFile("painBattery.mp3");
		this->evilTouch.setBuffer(this->evilTouchBuffer);
	}
}

void Player::initPlayer()
{
	this->player.setTexture(this->playerTexture);
	this->player.setScale(0.5f, 0.5f);

	this->currentFrame = sf::IntRect(0, 0, 313, 512);
	this->currentFrame.left = 60.f;

	this->player.setTextureRect(this->currentFrame);
	this->player.setOrigin(this->player.getPosition().x / 2,
		this->player.getPosition().y / 2);
}

void Player::updatePlayer()
{
	this->player.setTextureRect(this->currentFrame);
}

// constr & destr
Player::Player()
{
	this->initVariables();
	this->initSounds();
	this->initPlayer();
}

Player::~Player()
{}

// accessors
const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animSwitch;

	if (this->animSwitch)
		this->animSwitch = false;

	return anim_switch;
}

int Player::getHealth()
{
	return this->health;
}

// functions public
void Player::render(sf::RenderWindow& window)
{
	window.draw(this->player);
	window.draw(this->staminaBarAfter);
	window.draw(this->staminaBar);
	 
}

void Player::setOrigin(const sf::Vector2f& vector2f)
{
	this->player.setOrigin(vector2f);
}

void Player::crouch()
{
	this->batteryCollected.play();
	if (this->animTimer.getElapsedTime().asMilliseconds() >= 5.f || this->getAnimSwitch())
	{
		this->currentFrame.top = 1050.f;
		this->currentFrame.left += 570.f;
		if (this->currentFrame.left >= 630.f)
		{
			this->currentFrame.left = 60;
		}
		this->player.setTextureRect(this->currentFrame);
		this->animTimer.restart();
	}
}

void Player::evilCrouch()
{
	this->evilTouch.play();
	if (this->animTimer.getElapsedTime().asMilliseconds() >= 5.f || this->getAnimSwitch())
	{
		this->currentFrame.top = 1050.f;
		this->currentFrame.left += 570.f;
		if (this->currentFrame.left >= 630.f)
		{
			this->currentFrame.left = 60;
		}
		this->player.setTextureRect(this->currentFrame);
		this->animTimer.restart();
	}
}

sf::FloatRect Player::getGlobalBounds()
{
	return this->player.getGlobalBounds();
}

void Player::setPosition(const sf::Vector2f& vector2f)
{
	this->player.setPosition(vector2f);
}

void Player::resetAnimTimer()
{
	this->animTimer.restart();
	this->animSwitch = true;
}

sf::Sprite Player::getPlayer()
{
	return this->player;
}

void Player::update(sf::Event& ev)
{
	this->eventsPoll(ev);
	this->updateAnimations(ev);
	if (this->stamina > 0)
		this->staminaBar.setSize(sf::Vector2f(10 * this->stamina, 65));
	else
		this->staminaBar.setSize(sf::Vector2f(0, 65));
}

void Player::updateAnimations(sf::Event& ev)
{
	if (this->animState == IDLE)
	{
		this->footsteps.stop();

		if (this->animTimer.getElapsedTime().asSeconds() >= 0.5f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 570.f;
			if (this->currentFrame.left >= 630.f)
			{
				this->currentFrame.left = 60.f;
			}
			this->player.setTextureRect(this->currentFrame);
			this->animTimer.restart();
		}
	}
	if (this->animState == MOVING_LEFT)
	{
		if (this->animTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->footsteps.play();

			this->currentFrame.top = 512.f;
			this->currentFrame.left += 512.f;
			if (this->currentFrame.left >= 630.f)
			{
				this->currentFrame.left = 60.f;
			}
			this->player.setTextureRect(this->currentFrame);
			this->animTimer.restart();
		}
		this->player.setScale(0.5f, 0.5f);
		this->player.setOrigin(0.f, 0.f);
	}
	if (this->animState == MOVING_RIGHT)
	{
		if (this->animTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->footsteps.play();
			this->currentFrame.top = 512.f;
			this->currentFrame.left += 512.f;
			if (this->currentFrame.left >= 630.f)
			{
				this->currentFrame.left = 60.f;
			}
			this->player.setTextureRect(this->currentFrame);
			this->animTimer.restart();
		}
		this->player.setScale(-0.5f, 0.5f);
		this->player.setOrigin(this->player.getGlobalBounds().width / 3.f,0.f);

	}
}

int Player::getMaxHealth()
{
	return this->maxHealth;
}

void Player::setAnimStatus(const unsigned int& ANIM_SEE_ENUM)
{
	this->animState = ANIM_SEE_ENUM;
}

sf::Vector2f Player::getPosition()
{
	return this->player.getPosition();
}


void Player::setHealth(const unsigned short& number)
{
	this->health -= number;
}

void Player::footstepsStop()
{
	this->footsteps.stop();
}

void Player::updateSpeed(const float& dif)
{
	this->sprintSpeed /= (dif * 1.2f);
}

void Player::setHealth(const std::string& charr)
{
	this->health = std::stoi(charr);
}

void Player::eventsPoll(sf::Event& ev)
{
	this->animState = IDLE;
	this->moving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->animState = MOVING_LEFT;
		this->moveLeft();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->animState = MOVING_RIGHT;
		this->moveRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && this->moving)
	{
		if (this->stamina > 0)
		{
				this->sprint();
		}
		else
			this->speed = this->speedTemp - 10;
	}
	else
	{
		this->speed = this->speedTemp;
		if (this->stamina >= 100)
		{
			this->stamina = 100.f;
		}
		else
			this->stamina += this->staminaRevive;
	}
}

void Player::moveLeft()
{
	this->player.move(-this->speed, 0);
	this->moving = true;
}

void Player::moveRight()
{
	this->player.move(this->speed, 0);
	this->moving = true;
}

void Player::sprint()
{
	this->speed = sprintGoing;
	this->stamina -= 0.5f;
}