#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Enemy.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	int points;
	float timer;
	float maxTimer;
	int directione;

	void initvar();
	void initWindow();
	
	//Background
	sf::Sprite backgr;
	sf::Texture backgrTexture;
	void initbackground();

	//objekt statku gracza
	sf::Texture teksturagr;
	sf::Sprite player;
	void initgracz();
	//koniec obiektu statku gracza

	//Enemy w klasie game
	sf::Texture enemyText;
	std::vector<Enemy> enemies;
	void initenem();
	void bounce(std::vector<Enemy> &enemies);
	
	//Tekst pomocny
	sf::Text helpInGame;
	sf::Font font;
public:
	//Konstruktor
	Game() {
		this->initvar();
		this->initWindow();
		this->initgracz();
		this->initenem();
		this->initbackground();
	}
	//Destruktor - czyszczenie pamiêci po ka¿dej klatce
	virtual ~Game() {
		delete this->window;
	}
	//Metody
	void updatePollEvents();
	void updateenem();
	void update();

	void renderenem();
	void render();

	void moveEnemy();

	const bool isrunning() {
		return this->window->isOpen();
	}
};
