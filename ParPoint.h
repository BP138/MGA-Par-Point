#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Button.h"

class ParPoint
{

private:

	//Window, desktop, background variables
	sf::RenderWindow* window;
	sf::Vector2f desktopResolution;
	sf::VideoMode windowSize;
	sf::RectangleShape* background;
	sf::Texture* backgroundTexture;

	//Title variables
	sf::Font titleFont;
	sf::Text titleText;
	
	//Button variables
	Button* parpointButton;
	Button* hcpUploadButton;
	Button* settingsButton;


	//Clock and event variables
	float dt;
	sf::Event event;
	sf::Clock clock;

public:
	~ParPoint();
	ParPoint();

	void initializeVariables();
	void createWindowAndBackground();
	void createButtons();
	void createTitle();
	void run();
	void updateEvents();

	void update();
	void render();

};

