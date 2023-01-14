#include "help.h"

void help::initHelp()
{
	this->windowh = new sf::RenderWindow(sf::VideoMode(800, 600), "How to play");
	
}

void help::initbackground()
{
	if (!backgrTexture.loadFromFile("background.png")) {
		std::cout << "Failed to load background image";
		return;
	}
	this->backgrTexture.loadFromFile("background.png");
	this->backgr.setTexture(backgrTexture);
}



void help::updateEvents() {
	//Obs�uga wydarze� wewn�trz okna - wykrywanie event (czy co� si� sta�o)
	while (this->windowh->pollEvent(this->evh)) {
		switch (this->evh.type)
		{
		case sf::Event::Closed:
			this->windowh->close();
			break;
		case sf::Event::KeyPressed:
			if (evh.key.code == sf::Keyboard::Escape) this->windowh->close();
			if (evh.key.code == sf::Keyboard::F1) this->windowh->close();
			break;
		}
	}
}

void help::render()
{
	this->windowh->clear(); //Czyszczenie okna
	this->windowh->draw(this->backgr);
	this->windowh->draw(this->text);
	this->windowh->draw(this->header);
	this->windowh->display(); //Wy�wietlenie okna
}
