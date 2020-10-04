#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Button.h"

class ParPoint
{

private:
	

	//Window, desktop, background variables
	sf::Vector2f desktopResolution;
	sf::RenderWindow* window;
	sf::VideoMode windowSize;
	sf::RectangleShape* background;
	sf::Texture* backgroundTexture;

	//Mouse variables
	sf::Vector2i mousePos;

	//Title variables
	sf::Font titleFont;
	sf::Text titleText;
	
	//Button variables
	Button* parpointButton;
	Button* hcpUploadButton;
	Button* hcpFilebrowseButton;
	Button* settingsButton;

	//File variables
	std::string hcpReportFilepath;


	//Clock and event variables
	float dt;
	sf::Event event;
	sf::Clock clock;

public:
	~ParPoint();
	ParPoint();

	void initializeVariables();
	void createWindowAndBackground();
	void createMainMenuButtons();
	void createTitle();
	void run();
	void updateEvents();

	void update();
	void updateMouseClick(char mButtonClicked);
	void render();

};

