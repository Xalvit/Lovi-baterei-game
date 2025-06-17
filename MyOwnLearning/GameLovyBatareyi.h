#pragma once

#include "Menu.h"
#include "Player.h"
#include "Battery.h"
#include "Medkit.h"
#include <fstream>
#include <sstream>

class GameLoviBatareyi
{
private:
	// music
	sf::SoundBuffer musicBuffer;
	sf::Sound playMusic;
	sf::Sound menuMusic;
	sf::SoundBuffer menuBuffer;
	sf::SoundBuffer loseBuffer;
	sf::Sound lostSound;
	bool musicLostPlay;
	bool musicPlaying;
	bool nowMenuOpened;
	bool startplaymenu;
	// player stuff
	Player player;
	// variables

	Medkit medkit;
	Battery battery;
	GoofyBattery evilBattery;
	std::string pointsTemp;

	std::string points;
	bool dead;
	bool firstTimePlaying;
	bool isBoomed;
	bool inGameMenuOpen;

	std::string bestPoints;
	std::ifstream pointsInput;
	std::ofstream pointsOut;
	std::stringstream SgetStringFromFile;
	std::string getStringFromFile;

	bool tutorFirstTime;
	sf::Text pointsText;
	sf::Font pointsFont;

	sf::Clock timeToSeeBoom;
	sf::Clock batterySpawnTimer;
	sf::Clock tutorTimer;
	sf::Clock evilTimer;
	sf::Clock aidKitSpawnTimer;
	std::vector<Medkit> medkitVector;
	std::vector<Battery> batteryVector;
	std::vector<GoofyBattery> evilVector;
	int maxBatteriesNumber;
	bool tutorTime;
	bool gameStarted;
	bool gameStoped;
	bool logoShows;
	bool menuOpen;
	int logoShowCd;
	int maxAidkits;
	int howMuchHeal;
	float AidkitsTimeToSpawn;
	float dificultMultiplier;

	sf::SoundBuffer playbuffer;
	sf::Sound playsound;

	sf::Texture tutorTexture;
	sf::RectangleShape tutorShape;

	sf::Texture logoTexture;
	sf::RectangleShape logoShape;

	sf::Texture playButtonTexture;
	sf::RectangleShape playButton;

	sf::Texture menuTexture;
	sf::RectangleShape menuSprite;

	sf::Vector2f mouseViewPos;
	sf::Vector2i mousePos;

	sf::RectangleShape floor;
	sf::Texture floorTexture;

	sf::RectangleShape backGround;
	sf::Texture backGroundTexture;

	// window helpers
	sf::Event ev;
	sf::VideoMode mode;
	sf::RenderWindow *window;
	// Menu stuff
	Menu menu;
	// functions
	void loadCheck();
	void menuButtonFunctions();
	void spawnMedKit();
	void moveMedKits();
	void initPlayer();
	void spawnBattery();
	void updateCollisions();
	void mousePosUpdate();
	void initSound();
	void initMenu();
	void initWindow();
	void initVariables();
	void renderMenu();
	void initFloor();
	void initBG();
	void initTutor();
	void showTutor();
	void died();
	void renderBatteries();
	void checkBatteryFloor();
	void checkMedFloor();
	void checkCollectBattery();
	void moveEveryoneBattery();
	void restart();
	void spawnEvilBattery();
	void newBest();
	void checkCollectedMedkit();
	void loadBest();

	// accessors
	sf::Vector2u getWindowSize();

public:
	// Constructor & Destructor
	GameLoviBatareyi();
	~GameLoviBatareyi();

	// functions

	void update();
	void render();
	void pollEvents();

	// accessors

	bool isWindowOpen() const;
};

