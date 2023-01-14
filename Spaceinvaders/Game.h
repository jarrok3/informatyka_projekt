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

	int points;
	float timer;
	float maxTimer;

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
	int maxEnemies;
	sf::Texture teksturaenem;
	sf::Vector2f posenem;
	float speedEnemy;
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
	void updateenem();
	void update();

	void renderenem();
	void render();

	void moveEnemy();

	const bool isrunning() {
		return this->window->isOpen();
	}
};
