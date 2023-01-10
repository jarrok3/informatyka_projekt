#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	void initvar();
	void initWindow();

	sf::Sprite backgr;
	sf::Texture backgrTexture;
	void initbackground();

	//objekt statku gracza
	sf::Texture teksturagr;
	sf::Sprite player;
	void initgracz();
	//koniec obiektu statku gracza

	//obiekt pauza
	sf::Texture teksturapauz;
	sf::Sprite pauza;
	void initpauz();
	//koniec obiektu pauza

	//obiekt enemy
	sf::Texture teksturaenem;
	sf::Sprite enemy;
	void initenem();
	//koniec obiektu enemy
public:
	//Konstruktor
	Game() {
		this->initvar();
		this->initWindow();
		this->initgracz();
		this->initpauz();
		this->initenem();
		this->initbackground();
	}
	//Destruktor - czyszczenie pamiêci po ka¿dej klatce
	virtual ~Game() {
		delete this->window;
	}
	//Metody
	void updatePollEvents();
	void update();
	void render();
	const bool isrunning() {
		return this->window->isOpen();
	}
};
