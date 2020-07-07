#pragma once
#include <SFML/Graphics.hpp>


class Button
{
private:
	sf::RectangleShape button;
	sf::RectangleShape* fileTextbox;
	sf::CircleShape* fileBrowseButton;
	sf::Vector2f buttonSize;
	sf::Text buttonText;
	sf::Font buttonFont;

	bool isFileboxButton;

public:
	~Button();
	Button();
	Button(sf::Color bColor, std::string bText, 
		   sf::Vector2f bPosition, bool fileBox);
	int isClicked(sf::Vector2i mousePos);
	void drawButton(sf::RenderTarget* window);
	void setPosition(float x, float y);
};

