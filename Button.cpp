#include "Button.h"
#include <iostream>

Button::~Button()
{
	if (this->button) delete this->button;
}
Button::Button() //Needs updating
{
	this->isFileBrowserButton = false;
	//Set default button attributes
	this->rectButtonSize = sf::Vector2f(250.f, 40.f);
	//this->button->setSize(buttonSize);
	this->button->setFillColor(sf::Color::Red);
	this->button->setPosition(sf::Vector2f(200.f, 200.f));

	//Set default font and font attributes
	if (!this->buttonFont.loadFromFile("Resources/Fonts/Caviar_Dreams_Bold.ttf"))
	{
		std::cout << "error loading button font";
	}
	this->buttonText.setFont(buttonFont);
	this->buttonText.setString("PLACEHOLDER");
	this->buttonText.setFillColor(sf::Color::White);
	this->buttonText.setPosition(this->button->getPosition());
}


Button::Button(sf::Color bColor, std::string bText, sf::Vector2f bPosition, bool isFileBrowseButton)
{
	//Load and set font
	if (!this->buttonFont.loadFromFile("Resources/Fonts/Caviar_Dreams_Bold.ttf"))
		std::cout << "error loading button font";
	this->buttonText.setFont(buttonFont);

	//Set whether button uses a filebox/browseButton or not
	this->isFileBrowserButton = isFileBrowseButton;
	this->button = nullptr;
	this->rectButtonSize = sf::Vector2f(0, 0);
	this->circleButtonRadius = 0.f;

	if (!isFileBrowserButton)
	{
		//Set font and font attributes
		this->buttonText.setCharacterSize(40);
		this->buttonText.setString(bText);
		this->buttonText.setFillColor(sf::Color::White);
		this->buttonText.setOrigin(sf::Vector2f((this->buttonText.getGlobalBounds().width / 2.f),
								  (this->buttonText.getGlobalBounds().height / 2.f)));
		this->buttonText.setPosition(sf::Vector2f(bPosition.x, bPosition.y - 8.37f));

		//Set button attributes
		this->rectButtonSize = sf::Vector2f(this->buttonText.getGlobalBounds().width + 15.f,
											this->buttonText.getGlobalBounds().height + 15.f);
		this->button = new sf::RectangleShape(rectButtonSize);
		this->button->setFillColor(bColor);
		this->button->setOrigin(sf::Vector2f((rectButtonSize.x / 2.f), (rectButtonSize.y / 2.f)));
		this->button->setPosition(bPosition);
	}
	

	//create text box for file entering
	if (isFileBrowserButton)
	{
		this->buttonText.setString("");

		//Set up file browse button
		circleButtonRadius = 28.f;
		this->button = new sf::CircleShape(circleButtonRadius, 30U);
		this->button->setFillColor(sf::Color::Green);
		this->button->setOrigin(sf::Vector2f(circleButtonRadius, circleButtonRadius));
		this->button->setPosition(sf::Vector2f(bPosition.x + circleButtonRadius, bPosition.y));
	}
}


bool Button::isClicked(sf::Vector2i mousePos)
{
	if (this->button->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
		return true;

	else return false;
}

void Button::drawButton(sf::RenderTarget* window)
{
	window->draw(*this->button);
	window->draw(this->buttonText);
}

void Button::setPosition(float x, float y)
{
	this->button->setPosition(sf::Vector2f(x, y));
	if (!isFileBrowserButton)
		this->buttonText.setPosition(sf::Vector2f(x - (rectButtonSize.x / 2), y - (rectButtonSize.y / 2)));
}
sf::Vector2f Button::getPosition()
{
	return this->button->getPosition();
}

sf::Vector2f Button::getSize()
{
	if (!isFileBrowserButton)
		return this->rectButtonSize;
	else return sf::Vector2f(circleButtonRadius, 0.f);
}

sf::FloatRect Button::getGlobalBounds()
{
	return this->button->getGlobalBounds();
}