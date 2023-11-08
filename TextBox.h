#pragma once
#include <SFML/Graphics.hpp>
#include "Coordinates.h"
#include "Vector.h"
#include <iostream>
#include <string>

class TextBox
{
	sf::Text textarea;
	std::string text;
	sf::Font font;

	const int limit = 52;
	void deleteChar();
	bool checklimit();
public:
	TextBox();
	void processInputs(unsigned int inputchar);
	void Render(sf::RenderWindow* window);
	std::string getText() const;
};
