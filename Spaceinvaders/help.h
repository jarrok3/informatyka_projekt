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

	sf::Text header;

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

		header.setFont(font);
		header.setCharacterSize(50);
		header.setPosition(325, 100);
		header.setString("HELP");
		text.setFont(font);
		text.setString("Poruszanie po menu: \n  Arrow Up - ruch w gore \n  Arrow Down - ruch w dol \n  Enter - zatwierdz podswietlona opcje\n\nSterowanie:\n  Arrow Right - ruch w prawo\n  Arrow Left - ruch w lewo\n  Space - strzal\n  Escape - wyjscie z gry");
		text.setCharacterSize(20);
		text.setPosition(100,200);
	}
	const bool isrunning() {
		return this->windowh->isOpen();
	}
};

