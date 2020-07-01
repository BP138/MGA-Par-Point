#include "Button.h"
#include <iostream>

Button::~Button()
{}
Button::Button()
{
	//Set default button attributes
	this->buttonSize = sf::Vector2f(250.f, 40.f);
	this->button.setSize(buttonSize);
	this->button.setFillColor(sf::Color::Red);
	this->button.setPosition(sf::Vector2f(200.f, 200.f));

	//Set default font and font attributes
	if (!this->buttonFont.loadFromFile("Resources/Fonts/Caviar_Dreams_Bold.ttf"))
	{
		std::cout << "error loading button font";
	}
	this->buttonText.setFont(buttonFont);
	this->buttonText.setString("PLACEHOLDER");
	this->buttonText.setFillColor(sf::Color::White);
	this->buttonText.setPosition(this->button.getPosition());
}

Button::Button(sf::Color bColor, std::string bText, sf::Vector2f bPosition, bool fileBox)
{
	//Set fileTextbox to null for when it isn't used
	this->fileTextbox = nullptr;
	//Set font and font attributes
	if (!this->buttonFont.loadFromFile("Resources/Fonts/Caviar_Dreams_Bold.ttf"))
	{
		std::cout << "error loading button font";
	}
	this->buttonText.setFont(buttonFont);
	this->buttonText.setCharacterSize(40);
	this->buttonText.setString(bText);
	this->buttonText.setFillColor(sf::Color::White);
	this->buttonText.setOrigin(sf::Vector2f((this->buttonText.getGlobalBounds().width / 2.f),
		(this->buttonText.getGlobalBounds().height / 2.f)));
	this->buttonText.setPosition(sf::Vector2f(bPosition.x, bPosition.y - 8.37f));


	//Set button attributes
	this->buttonSize = sf::Vector2f(this->buttonText.getGlobalBounds().width + 15.f,
		this->buttonText.getGlobalBounds().height + 15.f);
	this->button.setSize(buttonSize);
	
	this->button.setFillColor(bColor);
	this->button.setOrigin(sf::Vector2f((this->button.getSize().x / 2.f),
										(this->button.getSize().y / 2.f)));
	this->button.setPosition(bPosition);


	
	//create text box for file entering
	if (fileBox)
	{
		this->fileTextbox = new sf::RectangleShape(sf::Vector2f(this->buttonSize.x , this->buttonSize.y));
		this->fileTextbox->setFillColor(sf::Color::White);
		this->fileTextbox->setPosition(bPosition.x,
									   bPosition.y - this->buttonSize.y / 2.f);

		this->buttonText.setOrigin(sf::Vector2f(((this->buttonText.getGlobalBounds().width + buttonSize.x)/ 2.f),
								                (this->buttonText.getGlobalBounds().height / 2.f)));
		this->button.setOrigin(sf::Vector2f(((this->buttonText.getGlobalBounds().width + buttonSize.x)/ 2.f),
			(this->button.getSize().y / 2.f)));
		//
	}
}


void Button::drawButton(sf::RenderTarget* window)
{
	window->draw(this->button);
	window->draw(this->buttonText);
	if (this->fileTextbox != nullptr) window->draw(*this->fileTextbox);
}

void Button::setPosition(float x, float y)
{
	this->button.setPosition(sf::Vector2f(x - (buttonSize.x / 2), y - (buttonSize.y / 2)));
	this->buttonText.setPosition(sf::Vector2f(x - (buttonSize.x / 2), y - (buttonSize.y / 2)));
}