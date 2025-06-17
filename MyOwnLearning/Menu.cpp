#include "Menu.h"

void Menu::initButtons()
{
	if (!this->blackTexture.loadFromFile("BlackScreenMenu.png"))
	{
		throw "BlackScreenMenu.png NOT FOUND";
	}
	else
	{
		this->blackTexture.loadFromFile("BlackScreenMenu.png");
		this->blackBackground.setTexture(&this->blackTexture);
	}



	this->buttonsFont.loadFromFile("timesnewromanpsmt.ttf");

	this->diedText.setFont(this->buttonsFont);
	this->diedText.setString("You Lost!");
	this->diedText.setScale(3.f, 3.f);
	this->diedText.setFillColor(sf::Color(255, 0, 0));

	this->musicButtonText.setFont(this->buttonsFont);
	this->musicButtonText.setString("Turn off music");
	this->musicButtonText.setScale(2, 2);

	this->offMusic.setFillColor(sf::Color(0, 204, 102));
	this->offMusic.setSize(sf::Vector2f(500, 150));
	this->offMusic.setOutlineColor(sf::Color(81, 81, 81));
	this->offMusic.setOutlineThickness(5.f);
	this->offMusic.setOrigin(sf::Vector2f(
		this->offMusic.getSize().x / 2,
		this->offMusic.getSize().y / 2));


	this->quitText.setFont(this->buttonsFont);
	this->quitText.setString("Quit");
	this->quitText.setScale(2, 2);

	this->quitButton.setFillColor(sf::Color(229, 98, 98));
	this->quitButton.setSize(sf::Vector2f(500,150));
	this->quitButton.setOutlineColor(sf::Color(81,81,81));
	this->quitButton.setOutlineThickness(5.f);
	this->quitButton.setOrigin(sf::Vector2f(
		this->quitButton.getSize().x / 2,
		this->quitButton.getSize().y / 2));


	this->restartText.setFont(this->buttonsFont);
	this->restartText.setString("Restart");
	this->restartText.setScale(2, 2);

	this->restartButton.setFillColor(sf::Color(182,112,223));
	this->restartButton.setSize(sf::Vector2f(500, 150));
	this->restartButton.setOutlineColor(sf::Color(81, 81, 81));
	this->restartButton.setOutlineThickness(5.f);
	this->restartButton.setOrigin(sf::Vector2f(
		this->restartButton.getSize().x / 2,
		this->restartButton.getSize().y / 2));

}

void Menu::initSounds()
{
	this->restartBuffer.loadFromFile("restart_sfx.mp3");
	this->restartSound.setBuffer(this->restartBuffer);
	this->restartSound.setVolume(25);

	this->quitBuffer.loadFromFile("exit_sfx.mp3");
	this->quitSound.setBuffer(this->quitBuffer);
	this->quitSound.setVolume(25);

	this->menuOpenBuffer.loadFromFile("open_sfx.mp3");
	this->menuOpenSound.setBuffer(this->menuOpenBuffer);
	this->menuOpenSound.setPlayingOffset(sf::seconds(5.f));
	this->menuOpenSound.setVolume(10);

	this->menuCloseBuffer.loadFromFile("close_sfx.mp3");
	this->menuCloseSound.setBuffer(this->menuCloseBuffer);
	this->menuCloseSound.setPlayingOffset(sf::seconds(3.f));
	this->menuCloseSound.setVolume(10);
}



// constr & destr
Menu::Menu()
{
	this->initSounds();
	this->initButtons();
}

Menu::~Menu(){}

void Menu::initMenu(sf::RenderWindow& window)
{
	this->menuShape.setFillColor(sf::Color(141, 139, 139));
	this->menuShape.setOutlineColor(sf::Color(50,50,50));
	this->menuShape.setOutlineThickness(7.5f);
	this->menuShape.setSize(sf::Vector2f(
		window.getSize().x/2,
		window.getSize().y/2));
	this->menuShape.setOrigin(sf::Vector2f(
		this->menuShape.getSize().x/2,
		this->menuShape.getSize().y/2));
}

void Menu::basicPosSet(sf::RenderWindow& window)
{
	this->blackBackground.setSize(sf::Vector2f(
		window.getSize().x, window.getSize().y));
	this->blackBackground.setPosition(sf::Vector2f(
		window.getPosition().x, window.getPosition().y));

	this->menuShape.setPosition(sf::Vector2f(
		window.getSize().x/2,
		window.getSize().y/2));

	this->offMusic.setPosition(sf::Vector2f(
		this->menuShape.getPosition().x,
		this->menuShape.getPosition().y));
	this->musicButtonText.setPosition(sf::Vector2f(
		this->offMusic.getPosition().x-170,
		this->offMusic.getPosition().y-40));

	this->restartButton.setPosition(sf::Vector2f(
		this->menuShape.getPosition().x,
		this->menuShape.getPosition().y - 170));
	this->restartText.setPosition(sf::Vector2f(
		this->restartButton.getPosition().x/2,
		this->restartButton.getPosition().y/2));

	this->quitButton.setPosition(sf::Vector2f(
		this->menuShape.getPosition().x,
		this->menuShape.getPosition().y + 170));

	this->quitText.setPosition(sf::Vector2f(
		this->quitButton.getPosition().x - 55,
		this->quitButton.getPosition().y - 35));

	this->restartText.setPosition(sf::Vector2f(
		this->restartButton.getPosition().x - 75,
		this->restartButton.getPosition().y - 35));

	this->diedText.setPosition(sf::Vector2f(this->menuShape.getSize().x - 180,
		this->menuShape.getSize().y - 400));
}

void Menu::setPos(sf::Vector2f& vika)
{
	this->menuShape.setPosition(vika);
}

void Menu::render(sf::RenderWindow& window)
{
	window.draw(this->blackBackground);
	window.draw(this->menuShape);
	window.draw(this->offMusic);
	window.draw(this->musicButtonText);
	window.draw(this->quitButton);
	window.draw(this->quitText);
	window.draw(this->restartButton);
	window.draw(this->restartText);
}

void Menu::restartButtonSoundPlay()
{
	this->restartSound.play();
}

void Menu::quitButtonSoundPlay()
{
	this->quitSound.play();
}

void Menu::showDiedText(sf::RenderWindow& window)
{
	window.draw(this->diedText);
}

void Menu::menuOpenSoundPlay()
{
	this->menuOpenSound.play();
	this->menuOpenSound.setPlayingOffset(sf::seconds(0.2f));
}

void Menu::menuCloseSoundPlay()
{
	this->menuCloseSound.play();
	this->menuCloseSound.setPlayingOffset(sf::seconds(0.6f));
}

void Menu::setMusicText(const std::string& onoroff)
{
	this->musicButtonText.setString(onoroff);
}

sf::RectangleShape Menu::getRestartButton()
{
	return this->restartButton;
}

sf::RectangleShape Menu::getQuitButton()
{
	return this->quitButton;
}

sf::RectangleShape Menu::getMusicOffButton()
{
	return this->offMusic;
}

void Menu::setColor(sf::Color color)
{
	this->offMusic.setFillColor(color);
}
