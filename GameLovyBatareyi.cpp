#include "GameLovyBatareyi.h"

// private functions
void GameLoviBatareyi::loadCheck()
{
	// Tutorial
	
	if (!this->tutorTexture.loadFromFile("tutorial.png"))
	{
		throw "tutorial.png NOT FOUND";
	}
	else
	{
		this->tutorTexture.loadFromFile("tutorial.png");
		this->tutorShape.setTexture(&this->tutorTexture);
	}

	// Font
	if (!this->pointsFont.loadFromFile("timesnewromanpsmt.ttf"))
	{
		throw "timesnewromanpsmt.ttf NOT FOUND";
	}
	else
	{
		this->pointsFont.loadFromFile("timesnewromanpsmt.ttf");
		this->pointsText.setFont(this->pointsFont);
	}

	// Menu BG
	if (!this->menuTexture.loadFromFile("menubg.png"))
	{
		throw "menubg.png NOT FOUND";
	}

	// Play button
	if (!this->playButtonTexture.loadFromFile("button_play.png"))
	{
		throw "button_play.png NOT FOUND";
	}
	// Logo
	if (!this->logoTexture.loadFromFile("logo.png"))
	{
		throw "logo.png NOT FOUND";
	}
	if (!this->playbuffer.loadFromFile("playsound.mp3"))
	{
		throw "playsound.mp3 NOT FOUND";
	}

	// Floor
	if (!this->floorTexture.loadFromFile("ground_ver2.png"))
	{
		throw "ground_ver2.png NOT FOUND";
	}
	else
	{
		this->floorTexture.loadFromFile("ground_ver2.png");
		this->floor.setTexture(&this->floorTexture);
	}

	// BackGround
	if (!this->backGroundTexture.loadFromFile("bg.png"))
	{
		throw "bg.png NOT FOUND";
	}
	else
	{
		this->backGroundTexture.loadFromFile("bg.png");
		this->backGround.setTexture(&this->backGroundTexture);
	}
}

void GameLoviBatareyi::menuButtonFunctions()
{
	if (menu.getRestartButton().getGlobalBounds().contains(this->mouseViewPos))
	{
		this->menu.restartButtonSoundPlay();
		this->restart();
		this->batteryVector.clear();
		this->evilVector.clear();
		this->medkitVector.clear();
		this->points = "0";
		this->inGameMenuOpen = true;
		this->nowMenuOpened = false;
		if (this->dead)
		{
			this->dead = !this->dead;
			this->musicLostPlay = false;
			this->lostSound.stop();
		}
		this->player.setPosition(sf::Vector2f(
			25,
			this->player.getPosition().y
		));
		this->playMusic.play();
	}
	if (menu.getQuitButton().getGlobalBounds().contains(this->mouseViewPos))
	{
		this->menu.quitButtonSoundPlay();
		if (std::stoi(this->points) > std::stoi(this->bestPoints))
			this->newBest();
		this->window->close();
	}
	if (menu.getMusicOffButton().getGlobalBounds().contains(this->mouseViewPos) && sf::Event::MouseButtonPressed)
	{
		if (this->musicPlaying)
		{
			this->menu.restartButtonSoundPlay();
			this->menu.setColor(sf::Color(255, 51, 51));
			this->playMusic.setVolume(0);
			this->lostSound.setVolume(0);
			this->menu.setMusicText("Turn on music");
			this->musicPlaying = false;
		}
		else if (!this->musicPlaying)
		{
			this->menu.restartButtonSoundPlay();
			this->menu.setColor(sf::Color(0, 204, 102));
			this->playMusic.setVolume(10);
			this->lostSound.setVolume(10.f);
			this->menu.setMusicText("Turn off music");
			this->musicPlaying = true;
			this->playMusic.play();
		}
	}
}

void GameLoviBatareyi::spawnMedKit()
{
	if (this->medkitVector.size() < this->maxAidkits)
	{
		if (!this->gameStoped)
		{
			if (this->aidKitSpawnTimer.getElapsedTime().asSeconds() >= this->AidkitsTimeToSpawn)
			{
				int chance = rand() % 50;
				if (chance == 1)
				{
					this->medkit.setPos(sf::Vector2f(
						(1 + rand() % this->window->getSize().x),
						-20
					));
					this->medkitVector.push_back(this->medkit);
					this->aidKitSpawnTimer.restart();
				}
			}
		}
	}
}

void GameLoviBatareyi::moveMedKits()
{
	if (this->medkitVector.size() > 0)
	{
		for (auto& var : this->medkitVector)
		{
			var.fly();
		}
	}
}

void GameLoviBatareyi::initPlayer()
{
	//this->player.setOrigin(sf::Vector2f(
	//this->player.getGlobalBounds().getSize().x,
	//this->pl
	//));
	this->player.setPosition(sf::Vector2f(
		0,
		this->floor.getGlobalBounds().top - 225
	));
}

void GameLoviBatareyi::spawnBattery()
{
	if (this->batteryVector.size() < this->maxBatteriesNumber)
	{
		if (!this->gameStoped)
		{
			if (this->batterySpawnTimer.getElapsedTime().asSeconds() >= this->dificultMultiplier)
			{

				this->battery.setPos(sf::Vector2f(
					(1 + rand() % this->window->getSize().x),
					-20
				));
				this->batteryVector.push_back(this->battery);
				this->batterySpawnTimer.restart();
			}
		}
	}
}

void GameLoviBatareyi::updateCollisions()
{
	if (this->player.getPosition().x < -25)
	{
		this->player.setPosition(sf::Vector2f(-25,
			this->player.getPosition().y));
	}
	if (this->player.getPosition().x > this->window->getSize().x-110)
	{
		this->player.setPosition(sf::Vector2f(this->window->getSize().x-110,
			this->player.getPosition().y));
	}

}

void GameLoviBatareyi::mousePosUpdate()
{
	this->mousePos = sf::Mouse::getPosition(*this->window);
	this->mouseViewPos = this->window->mapPixelToCoords(this->mousePos);

}

void GameLoviBatareyi::initSound()
{
	this->loseBuffer.loadFromFile("losesound.mp3");
	this->lostSound.setBuffer(this->loseBuffer);
	this->lostSound.setLoop(true);
	this->lostSound.setVolume(10);


	this->menuBuffer.loadFromFile("menuMusic.mp3");
	this->menuMusic.setBuffer(this->menuBuffer);
	this->menuMusic.setLoop(true);
	this->menuMusic.setVolume(10);

	this->musicBuffer.loadFromFile("inGameMusic.mp3");
	this->playMusic.setBuffer(this->musicBuffer);
	this->playMusic.setVolume(10);
	this->playMusic.setLoop(true);

	this->playbuffer.loadFromFile("playsound.mp3");
	this->playsound.setBuffer(this->playbuffer);
	this->playsound.setVolume(25.f);
}

void GameLoviBatareyi::initMenu()
{
	// MENU BACKGROUND
		float sizeX = sf::VideoMode::getDesktopMode().width;
		float sizeY = sf::VideoMode::getDesktopMode().height;
		this->menuTexture.loadFromFile("menubg.png");
		this->menuSprite.setTexture(&this->menuTexture);
		this->menuSprite.setSize(sf::Vector2f(sizeX, sizeY));

	// PLAY BUTTON
		this->playButtonTexture.loadFromFile("button_play.png");
		this->playButton.setTexture(&this->playButtonTexture);
		this->playButton.setSize(sf::Vector2f(this->playButtonTexture.getSize().x,
			this->playButtonTexture.getSize().y));
		this->playButton.setOrigin(sf::Vector2f(this->playButton.getTexture()->getSize() / 2u));
		this->playButton.setPosition(this->window->getView().getCenter());

	// LOGO
		this->logoTexture.loadFromFile("logo.png");
		this->logoShape.setTexture(&this->logoTexture);

		this->logoShape.setOrigin(sf::Vector2f(this->logoShape.getTexture()->getSize() / 2u));
		this->logoShape.setPosition(this->window->getView().getCenter());

		this->logoShape.setSize(sf::Vector2f(sizeX/2, sizeY/2));
}

void GameLoviBatareyi::initWindow()
{
	this->window = new sf::RenderWindow(
		sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),
		"Lovi Batareyi",
		sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setKeyRepeatEnabled(false);
}

void GameLoviBatareyi::initVariables()
{
	this->startplaymenu = false;
	this->nowMenuOpened = false;
	this->musicLostPlay = false;
	this->howMuchHeal = 1;
	this->points = "0";
	this->pointsTemp = this->points;
	this->inGameMenuOpen = true;
	this->isBoomed = false;
	this->getStringFromFile = "0";
	this->SgetStringFromFile << "";
	this->bestPoints = this->points;
	this->firstTimePlaying = true;
	

	this->AidkitsTimeToSpawn = 5.f;
	this->tutorFirstTime = true;
	this->tutorTime = false;
	this->gameStoped = false;
	this->gameStarted = false;
	this->maxBatteriesNumber = 4;
	this->logoShows = true;
	this->logoShowCd = 200;
	this->maxAidkits = 2;
	this->menuOpen = true;
	this->dead = false;
	this->loadCheck();
	this->initMenu();
	this->initSound();
	this->pointsText.setScale(1.2, 1.2);
	this->pointsText.setPosition(sf::Vector2f(
	this->window->getPosition().x + 15, 30));
	this->dificultMultiplier = 1.f;
	this->aidKitSpawnTimer.restart();
}

void GameLoviBatareyi::renderMenu()
{
	if (this->logoShowCd > 0)
	{
		if (this->logoShows)
			this->window->draw(this->logoShape);
			this->startplaymenu = true;
	}
	else
	{ 
		this->logoShows = false;
		if (this->menuOpen)
		{
			if (this->startplaymenu)
			{

				this->menuMusic.play();
				this->startplaymenu = false;
			}
			this->window->draw(this->menuSprite);
			this->window->draw(this->playButton);

		}
		else
		{
			this->menuMusic.stop();
		}
	}
	--logoShowCd;
}

void GameLoviBatareyi::initFloor()
{
	this->floor.setSize(sf::Vector2f(
	this->window->getSize().x,
	this->window->getSize().y/6
	));
	this->floor.setPosition(
		this->window->getPosition().x,
		static_cast<float>(sf::VideoMode::getDesktopMode().height)-150
		);
}

void GameLoviBatareyi::initBG()
{
	this->backGround.setSize(sf::Vector2f(this->window->getSize().x,
		this->window->getSize().y));
}

void GameLoviBatareyi::initTutor()
{
	this->tutorShape.setSize(sf::Vector2f(
		this->window->getSize().x, this->window->getSize().y));
	this->tutorShape.setPosition(sf::Vector2f(
		this->window->getPosition().x,this->window->getPosition().y));
}

void GameLoviBatareyi::showTutor()
{
	if (std::stoi(this->bestPoints) != 0)
	{ 
		this->tutorTime = false;
		this->gameStarted = true;
	}
	else
	{
		if (this->tutorTimer.getElapsedTime().asSeconds() <= 8.f)
		{
			this->window->draw(this->tutorShape);
			this->tutorFirstTime = false;
		}
		else
		{
			this->tutorTime = false;
			this->gameStarted = true;
		}
	}
}

void GameLoviBatareyi::died()
{
	this->dead = true;
	this->nowMenuOpened = !this->nowMenuOpened;
	this->inGameMenuOpen = !this->inGameMenuOpen;
	if (std::stoi(this->points) > std::stoi(this->bestPoints))
		this->newBest();
	if (!this->musicLostPlay)
	{
		this->lostSound.play();
	}
	this->musicLostPlay = true;
	this->menu.render(*this->window);
	this->menu.showDiedText(*this->window);
	this->playMusic.pause();
	this->player.footstepsStop();
}

void GameLoviBatareyi::renderBatteries()
{
	for (unsigned int i = 0; i < this->batteryVector.size(); i++)
	{
		this->window->draw(this->batteryVector[i].getShape());
	}
	for (unsigned int i = 0; i < this->evilVector.size(); i++)
	{
		this->window->draw(this->evilVector[i].getShape());
	}
	for (unsigned short i = 0;i < this->medkitVector.size();++i)
	{
		this->window->draw(this->medkitVector[i].getShape());
	}
}

void GameLoviBatareyi::checkBatteryFloor()
{
	sf::FloatRect bounds = this->floor.getGlobalBounds();
	for (auto& var : this->batteryVector)
	{
		unsigned short i = 0;
		if (bounds.intersects(var.getGlobalBounds()))
		{
			this->batteryVector.erase(this->batteryVector.begin() + i);
			this->player.setHealth(1);
		}
		++i;
	}
	for (auto& var : this->evilVector)
	{
		unsigned short i = 0;
		if (bounds.intersects(var.getGlobalBounds()))
		{
			this->evilVector.erase(this->evilVector.begin() + i);
		}
		++i;
	}

}

void GameLoviBatareyi::checkMedFloor()
{
	sf::FloatRect bounds = this->floor.getGlobalBounds();
	for (auto& var : this->medkitVector)
	{
		unsigned short i = 0;
		if (bounds.intersects(var.getGlobalBounds()))
		{
			this->medkitVector.erase(this->medkitVector.begin() + i);
		}
		++i;
	}
}

void GameLoviBatareyi::checkCollectBattery()
{
	sf::FloatRect plrBounds = this->player.getGlobalBounds();
	for (auto& var : this->batteryVector)
	{
		unsigned short i = 0;
		if (plrBounds.intersects(var.getGlobalBounds()))
		{
			int poin;
			poin = std::stoi(this->points);
			this->player.setAnimStatus(GOT_BATTERY);
			this->player.crouch();
			this->points = std::to_string(this->batteryVector[i].getBatteryCost()+poin);
			this->batteryVector.erase(this->batteryVector.begin() + i);
			if (std::stoi(this->points) == 100)
			{
				this->pointsTemp = this->points;
				this->dificultMultiplier -= 0.1;
				this->player.updateSpeed(this->dificultMultiplier);
			} 
			if (std::stoi(this->points) >= (100 + std::stoi(this->pointsTemp)))
			{
				if (this->dificultMultiplier > 0.2)
				{
					this->dificultMultiplier -= 0.1;
					this->player.updateSpeed(this->dificultMultiplier);
				}
				
				this->pointsTemp = this->points;
			}
		}
		++i;
	}

	for (auto& var : this->evilVector)
	{
		unsigned short i = 0;
		if (plrBounds.intersects(var.getGlobalBounds()))
		{
			this->player.setHealth(2);
			this->player.setAnimStatus(GOT_BATTERY);
			this->player.evilCrouch();
			this->evilBattery.setPosBom(sf::Vector2f(var.getPosition().x,var.getPosition().y));
			this->isBoomed = true;
			this->evilVector.erase(this->evilVector.begin() + i);
		}
		++i;
	}
}

void GameLoviBatareyi::moveEveryoneBattery()
{
	if (!this->gameStoped)
	{
		for (unsigned short i = 0; i < this->batteryVector.size(); ++i)
		{
			this->batteryVector[i].flyBattery();
		}
		for (unsigned short i = 0; i < this->evilVector.size(); ++i)
		{
			this->evilVector[i].flyBattery(1.7);
		}
	}
}

void GameLoviBatareyi::restart()
{
	this->dificultMultiplier = 1;
	this->player.setHealth("10");
	if (std::stoi(this->points) > std::stoi(this->bestPoints))
		this->newBest();
	this->points = "0";
}

void GameLoviBatareyi::spawnEvilBattery()
{
	if (this->evilVector.size() < 5)
	{
		if (this->evilTimer.getElapsedTime().asSeconds() >= this->dificultMultiplier)
		{
			unsigned int chance = rand() % 100;
			if (chance == 1)
			{
				if (!this->gameStoped)
				{
					this->evilBattery.setPos(sf::Vector2f(
						(1 + rand() % this->window->getSize().x + (100 + rand() % 500) - (100 + rand() % 500)),
						-20
					));
					this->evilVector.push_back(this->evilBattery);

				}
				this->evilTimer.restart();
			}
		}
	}
}

void GameLoviBatareyi::newBest()
{
	this->pointsOut.open("Points.txt", std::ofstream::in);
	this->pointsInput.open("Points.txt", std::ifstream::out);

	this->bestPoints = this->points;
	this->pointsOut << this->bestPoints;
	this->SgetStringFromFile << pointsInput.rdbuf();
	this->getStringFromFile = this->SgetStringFromFile.str();

	this->pointsInput.close();
	this->pointsOut.close();
}

void GameLoviBatareyi::checkCollectedMedkit()
{
	sf::FloatRect plrBounds = this->player.getGlobalBounds();
	for (auto& var : this->medkitVector)
	{
		unsigned short i = 0;
		if (plrBounds.intersects(var.getGlobalBounds()))
		{
			if (this->player.getHealth() + var.heal() > this->player.getMaxHealth())
			{
				this->medkit.playSadSound();
				this->medkitVector.erase(this->medkitVector.begin() + i);
			}
			else
			{
			this->medkit.playSound();
			this->player.setHealth(std::to_string(this->player.getHealth() + var.heal()));
			this->medkitVector.erase(this->medkitVector.begin() + i);
			}
		}
		++i;
	}
}

void GameLoviBatareyi::loadBest()
{
	this->pointsOut.open("Points.txt", std::ofstream::in);
	this->pointsInput.open("Points.txt", std::ifstream::out);

	this->SgetStringFromFile << pointsInput.rdbuf();
	this->getStringFromFile = this->SgetStringFromFile.str();
	this->bestPoints = this->getStringFromFile;

	this->pointsInput.close();
	this->pointsOut.close();
}

sf::Vector2u GameLoviBatareyi::getWindowSize()
{
	return this->window->getSize();
}

// Constructor & destructor
GameLoviBatareyi::GameLoviBatareyi()
{
	this->playMusic.play();
	this->playMusic.pause();
	this->initWindow();
	this->initVariables();
	this->loadBest();
	this->initFloor();
	this->initBG();
	this->initPlayer();
	this->initTutor();
	menu.initMenu(*this->window);
	menu.basicPosSet(*this->window);
	this->tutorTimer.restart();
	this->batterySpawnTimer.restart();
	this->timeToSeeBoom.restart();
	this->evilTimer.restart();

}

GameLoviBatareyi::~GameLoviBatareyi()
{
	delete this->window;
}

// public functions

void GameLoviBatareyi::update()
{
	this->window->clear();
	this->render();

	if (this->tutorTime)
	{
		if (this->tutorFirstTime)
			this->tutorTimer.restart();

		this->showTutor();
		this->playMusic.play();
		this->musicPlaying = true;
	}
	else if (this->gameStarted)
	{
		if (this->player.getHealth() > 0)
		{
				this->updateCollisions();
			if (this->inGameMenuOpen)
			{
				this->player.update(this->ev);
				this->spawnMedKit();
				this->spawnBattery();
				this->spawnEvilBattery();
				this->moveEveryoneBattery();
				this->moveMedKits();
				this->checkBatteryFloor();
				this->checkMedFloor();
				this->checkCollectBattery();
				this->checkCollectedMedkit();
			}
			else
			{
				this->menu.render(*this->window);
				this->playMusic.pause();
			}

			this->pointsText.setString("Points: " + this->points
				+ "\n\nHealth: " + std::to_string(this->player.getHealth())
				+ "\n\nYour Best: " + this->bestPoints);
		}
		else
		{
			this->died();
		}
	}
	this->window->display();
}

void GameLoviBatareyi::render()
{
	this->renderMenu();

	if (this->gameStarted)
	{
		this->window->draw(this->backGround);
		this->window->draw(this->floor);
		this->player.render(*this->window);
		this->window->draw(this->pointsText);
		if (this->isBoomed)
		{
			this->window->draw(this->evilBattery.bomShape());
			if (this->timeToSeeBoom.getElapsedTime().asSeconds() >= 0.5f)
			{
				this->isBoomed = false;
				this->timeToSeeBoom.restart();
			}
		}
		this->renderBatteries();
	}
}

void GameLoviBatareyi::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed) 
		{
			this->window->close();
		}
		if (this->ev.type == sf::Event::KeyReleased &&
			(this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D))
		{
			this->player.resetAnimTimer();
		}
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
		{
			if (this->gameStarted && !this->dead)
			{
				this->nowMenuOpened = !this->nowMenuOpened;
				this->inGameMenuOpen = !this->inGameMenuOpen;
				if (this->inGameMenuOpen)
				{
					this->menu.menuCloseSoundPlay();
					this->playMusic.play();
				}
				else
				{
					this->menu.menuOpenSoundPlay();
					this->playMusic.pause();
				}
				this->player.footstepsStop();
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->mousePosUpdate();
			if (this->nowMenuOpened)
			{
				this->menuButtonFunctions();
			}
			if (!this->gameStarted);
			{
				if (this->playButton.getGlobalBounds().contains(this->mouseViewPos) && this->menuOpen == true && !this->logoShows)
				{
					this->menuOpen = false;
					this->tutorTime = true;
					this->playsound.play();
				}
			}
		}
	}
}

// accessors
bool GameLoviBatareyi::isWindowOpen() const
{
	return this->window->isOpen();
}