#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Enemy.h"
#include "spaceship.h"
#include "Bullet.h"

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

	//obiekt statku gracza
	void initgracz();
	sf::Texture playerText;
	//spaceship player();
	//koniec obiektu statku gracza

	//Enemy w klasie game
	sf::Texture enemyText;
	std::vector<Enemy> enemies;
	void initenem();
	void bounce(std::vector<Enemy> &enemies);
	
	

	//Bullet w klasie game
	std::vector<Bullet> bullets;
	sf::Texture bulletTexture;
	void initbullets();

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
		this->initbullets();
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

	void updatePlayer();
	void renderPlayer();

	void isshooting();
	void renderbullet();

	const bool isrunning() {
		return this->window->isOpen();
	}
};
