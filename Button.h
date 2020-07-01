#pragma once
#include <SFML/Graphics.hpp>


class Button
{
private:
	sf::RectangleShape button;
	sf::RectangleShape* fileTextbox;
	sf::Vector2f buttonSize;
	sf::Text buttonText;
	sf::Font buttonFont;

public:
	~Button();
	Button();
	Button(sf::Color bColor, std::string bText, 
		   sf::Vector2f bPosition, bool fileBox);
	void drawButton(sf::RenderTarget* window);
	void setPosition(float x, float y);
};

