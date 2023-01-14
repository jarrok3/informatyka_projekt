#include "Game.h"

void Game::initgracz() {
	if (!teksturagr.loadFromFile("player.png")) {
		std::cout << "Failed to load player image";
		return;
	}
	this->teksturagr.loadFromFile("player.png");
	this->player.setTexture(teksturagr);
	this->player.scale(0.2f, 0.2f);
	this->player.setPosition(this->videomode.width / 2, 500);
}
void Game::initpauz() {
	if (!teksturapauz.loadFromFile("pause-button.png")) {
		std::cout << "Failed to load pause image";
		return;
	}
	this->teksturapauz.loadFromFile("pause-button.png");
	this->pauza.setTexture(teksturapauz);
	this->pauza.scale(0.1f, 0.1f);
	this->pauza.setPosition(this->videomode.width - 60, 10);
}
void Game::initenem() {
	if (!teksturaenem.loadFromFile("enemy.png")) {
		std::cout << "Failed to load enemy image";
		return;
	}
	this->teksturaenem.loadFromFile("enemy.png");
	this->enemy.setTexture(teksturaenem);
	this->enemy.scale(0.1f, 0.1f); //60x60 to nowy rozmiar
	this->posenem.x = 20.f;
	this->posenem.y = 20.f;
	this->enemy.setPosition(this->posenem);
}

void Game::initvar() {
	this->window = nullptr; //zainicjowanie pustego wskaŸnika window (nadanie wartoœci NULL)

	this->points = 0;
	this->timer = 0.f;
	this->maxTimer = 1000.f;
	this->maxEnemies = 10;
	this->speedEnemy = 10.f;
}

void Game::initWindow() {
	//nadanie rozmiaru okna
	this->videomode.height = 600;
	this->videomode.width = 800;
	//nadanie wskaŸnikowi window rozmiaru okna
	this->window = new sf::RenderWindow(this->videomode, "Projekt Space Invaders", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}
void Game::initbackground()
{
	if (!backgrTexture.loadFromFile("background.png")) {
		std::cout << "Failed to load background image";
		return;
	}
	this->backgrTexture.loadFromFile("background.png");
	this->backgr.setTexture(backgrTexture);
}
//end private metody

void Game::update() {
	//Obs³uga aktualizowania okna (zale¿nie od wydarzeñ)
	this->updatePollEvents();

	this->updateenem();


	//std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x <<" " <<sf::Mouse::getPosition(*this->window).y <<"\n";
}

void Game::updatePollEvents() {
	//Obs³uga wydarzeñ wewn¹trz okna - wykrywanie event (czy coœ siê sta³o)
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		}
	}
}

void Game::updateenem()
{
	//Updatuje timer dla ruchu enemies
	if (this->timer >= this->maxTimer)
	{
		this->timer = 0.f;
		this->moveEnemy();
	}
	else
		this->timer += 250.f;
	std::cout << this->timer << " timer \n";
}

void Game::moveEnemy()
{
	this->posenem.x += this->speedEnemy;
	this->enemy.setPosition(this->posenem);
}

void Game::renderenem()
{
	this->window->draw(enemy);
}

//rendering okna - wyswietlanie obiektów klatka po klatce
void Game::render() {
	this->window->clear(); //Czyszczenie okna
	this->window->draw(this->backgr);
	this->window->draw(this->player);
	this->window->draw(this->pauza);
	this->renderenem();
	this->window->display(); //Wyœwietlenie okna
}

//koniec klasy Game