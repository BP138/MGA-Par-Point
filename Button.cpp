#include "Button.h"
#include <iostream>

Button::~Button()
{
	delete this->fileTextbox;
}
Button::Button()
{
	//Set default button attributes
	this->buttonSize = sf::Vector2f(250.f, 40.f);
	this->button.setSize(buttonSize);
	this->button.setFillColor(sf::Color::Red);
	this->button.setPosition(sf::Vector2f(200.f, 200.f));
	this->fileTextbox = nullptr;

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
	//Set whether button uses a filebox/browseButton or not
	this->isFileboxButton = fileBox;

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

	//Set fileTextbox to null for when it isn't used
	this->fileTextbox = nullptr;
	
	//create text box for file entering
	if (fileBox)
	{
		this->fileTextbox = new sf::RectangleShape(sf::Vector2f(this->buttonSize.x , this->buttonSize.y));
		this->fileTextbox->setFillColor(sf::Color::White);
		this->fileTextbox->setOrigin(sf::Vector2f(this->fileTextbox->getOrigin().x,
						this->fileTextbox->getOrigin().y + this->fileTextbox->getGlobalBounds().height / 2.f));
		this->fileTextbox->setPosition(bPosition.x,
									   bPosition.y);
		this->button.setPosition(sf::Vector2f(bPosition.x - this->button.getGlobalBounds().width / 2.f,
											  bPosition.y));
		this->buttonText.setPosition(sf::Vector2f(bPosition.x - this->button.getGlobalBounds().width / 2.f,
			bPosition.y));

		//Set up file browse button
		this->fileBrowseButton = new sf::CircleShape(28.f, 30U);
		float fbbRadius = this->fileBrowseButton->getRadius();
		this->fileBrowseButton->setFillColor(sf::Color::Green);
		this->fileBrowseButton->setOrigin(sf::Vector2f((fbbRadius),
													   (fbbRadius)));
		this->fileBrowseButton->setPosition(sf::Vector2f(this->fileTextbox->getPosition().x + 
														 this->fileTextbox->getGlobalBounds().width + 
														(this->fileBrowseButton->getRadius()),
														 this->fileTextbox->getPosition().y));
		
	}
}


int Button::isClicked(sf::Vector2i mousePos)
{
	if (!isFileboxButton)
	{
		if (this->button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
		{
			return 1;

		}
	}
	if (isFileboxButton)
	{
		if (this->button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
		{
			return 1;

		}
		else if (this->fileTextbox->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) ||
				 this->fileBrowseButton->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
		{
			return 2;
		}
	}
	else return false;
}

void Button::drawButton(sf::RenderTarget* window)
{
	window->draw(this->button);
	window->draw(this->buttonText);
	if (this->fileTextbox != nullptr)
	{
		window->draw(*this->fileTextbox);
		window->draw(*this->fileBrowseButton);
	}
}

void Button::setPosition(float x, float y)
{
	this->button.setPosition(sf::Vector2f(x - (buttonSize.x / 2), y - (buttonSize.y / 2)));
	this->buttonText.setPosition(sf::Vector2f(x - (buttonSize.x / 2), y - (buttonSize.y / 2)));
}