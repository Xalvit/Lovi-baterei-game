#include "Worm.h"

// private functions

void Worm::initVariables()
{
	this->BallDeleteCDMax = 100;
	this->BallDeleteCD = this->BallDeleteCDMax;
	this->BallSpawnCDMax = 0.01f;
	this->BallSpawnCD = BallSpawnCDMax;
	 this->WormMaxLength = 9;
}

void Worm::deleteNSpawnBall()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->spawnBall();
		this->BallDeleteCD = this->BallDeleteCDMax;
	}
	else
	{
		if (this->WormBody.size() != 0)
		{
			this->BallDeleteCD -= 1;
			this->WormBody.pop_front();
		}
	}
}

void Worm::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1500, 1000), "Lil worm :)", sf::Style::Default);
	this->window->setFramerateLimit(165);
}

void Worm::spawnBall()
{
	if (WormBody.size() <= WormMaxLength)
	{
		while (BallSpawnCD > 0) // CD for ballSpawn
		{
			BallSpawnCD -= 1.f;
		}
		Ball shape;
		shape.setPosition(static_cast<sf::Vector2f>(this->GetMousePos()));
		WormBody.push_back(shape);
	}
	else
	{
		WormBody.pop_front();
	}
}

// constr & destr
Worm::Worm()
{
	this->initWindow();
	this->initVariables();

}

Worm::~Worm()
{
	delete this->window;
}

// accessors
bool Worm::isWindowOpen() const
{
	return this->window->isOpen();
}

sf::Vector2i Worm::GetMousePos()
{
	return sf::Mouse::getPosition(*this->window);
}

// functions
void Worm::update()
{
	this->window->clear();
	this->deleteNSpawnBall();
	this->render();
	this->window->display();
}

void Worm::render()
{
	for (auto it = WormBody.begin();it != WormBody.end();++it)
	{
		this->window->draw(it->getShape());
	}
}

void Worm::pollEvent()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed) 
		{
			this->window->close();
		}
		if (this->event.key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
		if (this->event.key.code == sf::Keyboard::Backspace)
		{
			this->WormBody.clear();
		}
	}
}





