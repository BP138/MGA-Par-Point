#include "ParPoint.h"
#include <iostream>
#include <string>


ParPoint::ParPoint()
{
	initializeVariables();
	createWindowAndBackground();
	createMainMenuButtons();
	createTitle();
}
ParPoint::~ParPoint()
{
	delete this->window;
	delete this->background;
	delete this->backgroundTexture;
}

void ParPoint::initializeVariables()
{
	//Get user's desktop resolution
	this->desktopResolution = sf::Vector2f(sf::VideoMode::getDesktopMode().width,
										   sf::VideoMode::getDesktopMode().height);

	//Set window and background pointers to null, set windowsize
	this->window = nullptr;
	this->windowSize.width = 1440.f * .9f;
	this->windowSize.height = 1110.f * .9f;
	this->background = nullptr;
	this->backgroundTexture = nullptr;

	//Initialize clickedMousePos and dt
	this->mousePos = sf::Vector2i(0, 0);
	this->dt = 0.f;

	//Initialize title font/text
	//this->titleFont.
	if (!this->titleFont.loadFromFile("Resources/Fonts/AlexBrush-Regular.ttf"))
		std::cout << "error loading button font";
	else this->titleText.setFont(titleFont);
	this->titleText.setString("titleText placeholder");

	//Initialize buttons
	this->parpointButton = nullptr;
	this->hcpUploadButton = nullptr;
	this->settingsButton = nullptr;
}


void ParPoint::createWindowAndBackground()
{
	//Set the window
	this->window = new sf::RenderWindow(windowSize, "Par Point",
		sf::Style::Close | sf::Style::Resize);
	this->window->setFramerateLimit(30);

	//Set the background
	this->background = new sf::RectangleShape(sf::Vector2f
	(
		static_cast<float>(windowSize.width),
		static_cast<float>(windowSize.height)
	));

	//Create texture, load background photo, set the texture
	this->backgroundTexture = new sf::Texture;
	if (!(*backgroundTexture).loadFromFile("Resources/hamilton_mill.jpg"))
		std::cout << "HM background texture failed to load";
	this->background->setTexture(this->backgroundTexture);
		
}

void ParPoint::createMainMenuButtons()
{
	//Par Point button
	this->parpointButton = new Button(sf::Color::Red, "ParPoint",
					sf::Vector2f(windowSize.width / 2.f, windowSize.height * .65f),
					false);

	//Settings button
	this->settingsButton = new Button(sf::Color::Red, "Settings",
		sf::Vector2f(windowSize.width / 2.f, windowSize.height * .8f),
		false);

	//Handicap report upload button, includes textbox
	this->hcpUploadButton = new Button(sf::Color::Red, "Update Handicap Report",
		sf::Vector2f(windowSize.width / 2.f, windowSize.height * .725f), false);

	this->hcpFilebrowseButton = new Button(sf::Color::Green, "",
		sf::Vector2f(hcpUploadButton->getPosition().x + (hcpUploadButton->getGlobalBounds().width / 2.f) 
				   , windowSize.height * .725f)
				   , true);
	
	

}


//Creates main menu title text
void ParPoint::createTitle()
{
	
	this->titleText.setCharacterSize(110);
	this->titleText.setString("Hamilton Mill \n  Par Point");
	this->titleText.setFillColor(sf::Color::White);
	this->titleText.setOrigin(titleText.getGlobalBounds().width / 2.f,
		(titleText.getGlobalBounds().height / 2.f));
	this->titleText.setPosition((windowSize.width / 2.f), windowSize.height * .132f);
	

}

//Starts game loop
void ParPoint::run()
{
	while (this->window->isOpen())
	{
		this->dt = this->clock.restart().asSeconds(); //May have to move this to end of loop
		this->updateEvents();
		this->update();
		this->render();
	}
}

void ParPoint::updateEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		//window closed event
		case sf::Event::Closed:
			this->window->close();
			break;

		//window resize event
		case sf::Event::Resized:
			printf("New window width: %i New window height: %i\n",
				   this->event.size.width, this->event.size.height);
			break;

		//Mouse clicked event
		case sf::Event::MouseButtonPressed:
			this->mousePos = sf::Mouse::getPosition(*window);
			std::cout << mousePos.x << ", " << mousePos.y << std::endl;

			if (event.mouseButton.button == sf::Mouse::Left)
				this->updateMouseClick('L');
			else if (event.mouseButton.button == sf::Mouse::Right)
				this->updateMouseClick('R');


			this->updateMouseClick(event.mouseButton.button);
			break;

		default: break;

		}
	}
}

void ParPoint::update()
{

}

void ParPoint::updateMouseClick(char mButtonClicked)
{
	//Check if ParPoint button was clicked
	if (this->parpointButton->isClicked(this->mousePos))
	{
		if (mButtonClicked == 'L')
			std::cout << "Left click on ParPoint button" << std::endl;
		else if (mButtonClicked == 'R')
			std::cout << "Right click on ParPoint button" << std::endl;
	}

	//Check if Settings button was clicked
	 else if (this->settingsButton->isClicked(mousePos))
	{
		if (mButtonClicked == 'L')
			std::cout << "Left click on Settings button" << std::endl;
		else if (mButtonClicked == 'R')
			std::cout << "Right click on Settings button" << std::endl;
	}

	//Check if upload button is clicked
	else if (this->hcpUploadButton->isClicked(mousePos))
	{
		if (mButtonClicked == 'L')
			std::cout << "Left click on Handicap-Upload button" << std::endl;
		else if (mButtonClicked == 'R')
			std::cout << "Right click on Handicap-Upload button" << std::endl;
	}
	//Check if handicap texbox or browse button clicked
	else if (this->hcpFilebrowseButton->isClicked(mousePos))
	{
		if (mButtonClicked == 'L')
		{
			std::cout << "Left click on file browse button" << std::endl;

		}
		else if (mButtonClicked == 'R')
			std::cout << "Right click on Handicap textbox or browse button" << std::endl;
	}

	
}

void ParPoint::render()
{
	this->window->clear();
	this->window->draw(*this->background);
	this->window->draw(titleText);
	this->parpointButton->drawButton(window);
	this->hcpUploadButton->drawButton(window);
	this->hcpFilebrowseButton->drawButton(window);
	this->settingsButton->drawButton(window);

	this->window->display();
}