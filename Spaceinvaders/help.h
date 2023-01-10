#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
class help
{
private:
	sf::RenderWindow* windowh;
	sf::Event evh;

	sf::Sprite backgr;
	sf::Texture backgrTexture;
	void initbackground();

	sf::Font font;
	sf::Text text;

	void initHelp();
public:
	//kontruktor okna pomocy
	help() {
		initHelp();
		initbackground();
		createText();
	}
	//destruktor okna pomocy
	virtual ~help() {
		delete this->windowh;
	}

	void updateEvents();
	void render();
	void createText() {
		font.loadFromFile("retro.ttf");

		text.setFont(font);
		text.setString("This is some text in an existing class that creates a window.");
		text.setCharacterSize(20);
		text.setPosition(100,200);
	}
	const bool isrunning() {
		return this->windowh->isOpen();
	}
};

