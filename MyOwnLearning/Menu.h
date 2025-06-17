#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu
{
private:
	// variables
	sf::SoundBuffer restartBuffer;
	sf::SoundBuffer quitBuffer;
	sf::SoundBuffer menuOpenBuffer;
	sf::SoundBuffer menuCloseBuffer;
	sf::Sound restartSound;
	sf::Sound quitSound;
	sf::Sound menuOpenSound;
	sf::Sound menuCloseSound;

	

	sf::RectangleShape blackBackground;
	sf::Texture blackTexture;

	sf::RectangleShape offMusic;
	sf::Text musicButtonText;

	sf::Font buttonsFont;
	sf::Text restartText;
	sf::Text quitText;

	sf::Text diedText;

	sf::RectangleShape menuShape;
	sf::RectangleShape restartButton;
	sf::RectangleShape quitButton;
	void initButtons();
	void initSounds();

public:
	// constr & destr
	Menu();
	~Menu();

	void initMenu(sf::RenderWindow& window);
	void basicPosSet(sf::RenderWindow& window);
	void setPos(sf::Vector2f& vika);
	void render(sf::RenderWindow& window);
	void restartButtonSoundPlay();
	void quitButtonSoundPlay();
	void showDiedText(sf::RenderWindow& window);
	void menuOpenSoundPlay();
	void menuCloseSoundPlay();
	void setMusicText(const std::string& onoroff);
	sf::RectangleShape getRestartButton();
	sf::RectangleShape getQuitButton();
	sf::RectangleShape getMusicOffButton();
	void setColor(sf::Color color);
};

