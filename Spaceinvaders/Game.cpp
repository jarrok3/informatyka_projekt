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
	this->enemyText.loadFromFile("enemy.png");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++) {
			enemies.push_back(Enemy(&enemyText, sf::Vector2f(10.f + 70 * i, 10.f + 75 * j)));
		}
	}
}



void Game::initvar() {
	this->window = nullptr; //zainicjowanie pustego wskaŸnika window (nadanie wartoœci NULL)

	this->points = 0;
	this->timer = 0.f;
	this->maxTimer = 1000.f;
	this->directione = 1;
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

void Game::bounce(std::vector<Enemy>& enemies)
{
	/*for (auto& enemy : enemies) {
		if (enemy.enemySprite.getPosition().x < 0) {
			enemy.direction = 1;
			enemy.position.y += 8;
		}
		else if (enemy.enemySprite.getPosition().x > 740) {
			enemy.direction = -1;
			enemy.position.y += 8;
		}
	}*/
	for (auto& enemy : enemies) {
		enemy.moveEnemy(&directione);
		if (enemy.enemySprite.getPosition().x < 0 || enemy.enemySprite.getPosition().x >740) {
			for (auto& enemy : enemies) {
				enemy.position.y += 15;
			}
			this->directione *= -1;
		}
	}
}

void Game::updateenem()
{
	//Updatuje timer dla ruchu enemies
	if (this->timer >= this->maxTimer)
	{
		this->timer = 0.f;
		for (size_t i = 0; i < enemies.size(); i++) {
			this->bounce(enemies);
		}
	}
	else
		this->timer += 250.f;
	std::cout << this->timer << " timer \n";
}

void Game::renderenem()
{
	for (size_t i = 0; i < enemies.size(); i++) {
		this->window->draw(enemies[i].enemySprite);
	}
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