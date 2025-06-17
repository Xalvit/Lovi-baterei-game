#pragma once

#include "Ball.h"

class Worm
{
private:
	// variables
	float BallRadius;
	int BallSpawnCD;
	int BallSpawnCDMax;
	int BallDeleteCD;
	int BallDeleteCDMax;
	int WormMaxLength;

	std::list<Ball> WormBody;

	// window variables
	sf::RenderWindow* window;
	sf::Event event;

	// funct
	void initVariables();
	void deleteNSpawnBall();
	void initWindow();
	void spawnBall();

public:
	// const & destr
	Worm();
	~Worm();
	// accessors	
	bool isWindowOpen() const;
	sf::Vector2i GetMousePos();

	// functions
	void update();
	void render();
	void pollEvent();
};

