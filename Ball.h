#pragma once

#include <SFML/Graphics.hpp>
#include <list>

class Ball
{
private:
	// variables
	sf::CircleShape shape;
	// functions
	int BallRadius;
	void initBalls();
	//void Disappear();
public:
	// constr
	Ball();
	// function
	void renderBall();
	sf::CircleShape getShape();
	void setPosition(sf::Vector2f vec);
};

