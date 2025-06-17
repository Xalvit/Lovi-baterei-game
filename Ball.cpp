#include "Ball.h"

// private functions
void Ball::initBalls()
{
	this->BallRadius = 30.f;
	this->shape.setFillColor(sf::Color(200, 215, 255));
	this->shape.setRadius(BallRadius);
}

// constr
Ball::Ball()
{
	this->initBalls();
}

void Ball::renderBall()
{

}

sf::CircleShape Ball::getShape()
{
	return this->shape;
}

// functions
void Ball::setPosition(sf::Vector2f vec)
{
	this->shape.setPosition(vec);
}