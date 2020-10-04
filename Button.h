#pragma once
#include <SFML/Graphics.hpp>


class Button
{
private:
	sf::Shape* button;
	sf::Vector2f rectButtonSize;
	float circleButtonRadius;


	sf::Font buttonFont;
	sf::Text buttonText;
	
	bool isFileBrowserButton;

public:
	
	
	~Button();
	Button();
	Button(sf::Color bColor, std::string bText, 
		   sf::Vector2f bPosition, bool fileBox);
	bool isClicked(sf::Vector2i mousePos);
	void drawButton(sf::RenderTarget* window);
	void setPosition(float x, float y);
	sf::Vector2f getPosition();

	sf::Vector2f getSize();
	sf::FloatRect getGlobalBounds();
};

