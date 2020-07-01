#include "ParPoint.h"
#include <iostream>
#include <string>

ParPoint::~ParPoint()
{
	delete this->window;
	delete this->background;
	delete this->backgroundTexture;
}
ParPoint::ParPoint()
{
	initializeVariables();
	createWindowAndBackground();
	createButtons();
	createTitle();
}


void ParPoint::initializeVariables()
{
	//Get desktop resolution
	this->desktopResolution = sf::Vector2f(sf::VideoMode::getDesktopMode().width,
											sf::VideoMode::getDesktopMode().height);

	//Set window and background pointers to null, set windowsize
	this->window = nullptr;
	this->windowSize.width = 1440.f * .9f;
	this->windowSize.height = 1110.f * .9f;
	this->background = nullptr;

	this->dt = 0.f;
}


void ParPoint::createWindowAndBackground()
{
	this->window = new sf::RenderWindow(windowSize, "Par Point",
		sf::Style::Close | sf::Style::Resize);
	this->window->setFramerateLimit(30);

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

void ParPoint::createButtons()
{

	this->parpointButton = new Button(sf::Color::Red, "ParPoint",
					sf::Vector2f(windowSize.width / 2.f, windowSize.height * .65f), false);

	this->hcpUploadButton = new Button(sf::Color::Red, "Update Handicap Report",
		sf::Vector2f(windowSize.width / 2.f, windowSize.height * .725f), true);


	this->settingsButton = new Button(sf::Color::Red, "Settings",
					sf::Vector2f(windowSize.width / 2.f, windowSize.height * .8f), false);

}


void ParPoint::createTitle()
{

	if (!this->titleFont.loadFromFile("Resources/Fonts/AlexBrush-Regular.ttf"))
	{
		std::cout << "error loading button font";
	}
	this->titleText.setFont(titleFont);
	this->titleText.setCharacterSize(110);
	this->titleText.setString("Hamilton Mill \n  Par Point");
	this->titleText.setFillColor(sf::Color::White);
	this->titleText.setPosition((windowSize.width / 2.f), windowSize.height * .132f);
	this->titleText.setOrigin(titleText.getGlobalBounds().width  / 2.f,
								(titleText.getGlobalBounds().height  / 2.f));

}


void ParPoint::run()
{
	while (this->window->isOpen())
	{
		this->dt = this->clock.restart().asSeconds();
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

		default: break;
		}
	}
}

void ParPoint::update()
{

}


void ParPoint::render()
{
	this->window->clear();
	this->window->draw(*this->background);
	this->window->draw(titleText);
	this->parpointButton->drawButton(window);
	this->hcpUploadButton->drawButton(window);
	this->settingsButton->drawButton(window);

	this->window->display();
}