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
	int level;
	float timer;
	float maxTimer;
	sf::Vector2f directione;

	float enemySpeed;

	void initvar();
	void initWindow();
	
	//Background
	sf::Sprite backgr;
	sf::Texture backgrTexture;
	void initbackground();

	//obiekt statku gracza
	void initgracz();
	sf::Texture playerText;
	sf::Sprite playerSprite;
	sf::Vector2f playerPosition;
	float shotCooldown;
	int playerSpeed;
	//koniec obiektu statku gracza


	//Enemy w klasie game
	sf::Texture enemyText;
	std::vector<Enemy*> enemies;
	void initenem();
	
	

	//Bullet w klasie game
	std::vector<Bullet*> bullets;
	sf::Texture bulletTexture;
	void initbullets();

	//Tekst pomocny
	sf::Text helpInGame;
	sf::Font font;
	sf::Text gameWon;
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
	void updateBullets();
	void updateCollision();
	int updateGameState();

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
