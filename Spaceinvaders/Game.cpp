#include "Game.h"
#include "help.h"
#include "spaceship.h"

void Game::initenem() {
	this->enemyText.loadFromFile("enemy.png");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++) {
			this->enemies.push_back(new Enemy(&enemyText, sf::Vector2f(10.f + 100 * i, 60.f + 75 * j)));
		}
	}
	this->enemySpeed = 3.f * this->level * 0.4;
}

void Game::initgracz() {
	this->playerText.loadFromFile("player.png");
	this->playerSprite.setTexture(this->playerText);
	this->playerSprite.setScale(0.2f, 0.2f);
	this->playerPosition.x = 350.f;
	this->playerPosition.y = 500.f;
	this->playerSprite.setPosition(this->playerPosition);
	this->playerSpeed = 5;
}

void Game::initvar() {
	this->window = nullptr; //zainicjowanie pustego wskaźnika window (nadanie wartości NULL)
	this->level = 1;
	this->points = 0;
	this->timer = 0.f;
	this->maxTimer = 1000.f;
	this->directione.x = 1.f;
	this->directione.y = 0.f;
	this->shotCooldown = 0; 
}

void Game::initWindow() {
	//nadanie rozmiaru okna
	this->videomode.height = 600;
	this->videomode.width = 800;
	//nadanie wskaźnikowi window rozmiaru okna
	this->window = new sf::RenderWindow(this->videomode, "Projekt Space Invaders", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

	this->font.loadFromFile("retro.ttf");
	this->helpInGame.setCharacterSize(14);
	this->helpInGame.setPosition(10, 5);
	this->helpInGame.setFont(this->font);
	this->helpInGame.setString("F1 - How To Play\nDestroyed Invaders: " +std::to_string(this->points) + "\nLevel: " + std::to_string(this->level));

	this->gameWon.setCharacterSize(50);
	this->gameWon.setPosition(225, 200);
	this->gameWon.setFont(this->font);
	this->gameWon.setString("  YOU WIN!\nGAME OVER");
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

void Game::initbullets()
{
	this->bulletTexture.loadFromFile("bullet.png");
}
//end private metody

void Game::update() {
	//Obsługa aktualizowania okna (zależnie od wydarzeń)
	
	this->updatePollEvents();
	if (this->updateGameState() == 1) {

		this->updateCollision();

		this->updateenem();
		this->updatePlayer();
		this->isshooting();

		this->updateBullets();
	}
}

int Game::updateGameState() {
	int state = 1;
	if (this->enemies.size() <= 0 && this->level == 3) {
		state = 0;
	}
	else if (this->enemies.size() <= 0 && this->level < 3) {
		this->level++;
		this->initenem();
	}
	return state;
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets) {
		bullet->moveBullet();
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			std::cout << "updateBullets :: I HIT THE TOP - GOODBYE\n";
		}
		counter++;
	}
}

void Game::updateCollision()
{
	
	for (int i = 0; i< this->enemies.size(); i++) {
		bool enemy_killed = false;
		for (int k = 0; k < this->bullets.size() && enemy_killed == false; k++) {
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds())) {
				std::cout << bullets.size() << "BULLETS\n";
				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				std::cout << bullets.size() << "BULLETS AFTER HIT\n";
				this->points += 1;
				this->helpInGame.setString("F1 - How To Play\nDestroyed Invaders: " + std::to_string(this->points) + "\nLevel: " + std::to_string(this->level));
				
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				std::cout << enemies.size() << "ENEMIES\n";

				enemy_killed = true;
			}	
		}
	}
}

void Game::updatePollEvents() {
	//Obsługa wydarzeń wewnątrz okna - wykrywanie event (czy coś się stało)
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
			if (ev.key.code == sf::Keyboard::F1)
			{
				help helpWindow;
				while (helpWindow.isrunning()) {

					//Update okna po zdefiniowaniu event

					helpWindow.updateEvents();
					//czyszczenie poprzedniej klatki

					helpWindow.render();
					//Wyświetlenie okna
				}
			}
			break;
		}
	}
}

void Game::updateenem()
{
	for (auto* enemy : this->enemies) {
		enemy->moveEnemy(this->directione, this->enemySpeed);
		if (enemy->enemySprite.getPosition().x < 0 || enemy->enemySprite.getPosition().x >740) {
			for (auto* enemy : this->enemies) {
				enemy->enemySprite.move(0.f, 15.f);
			}
			this->directione.x *= -1;
			std::cout << "bounce :: BOUNCED \n";
		}
	}
}

void Game::updatePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->playerPosition.x<730) {
		this->playerPosition.x += this->playerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->playerPosition.x>=0) {
		this->playerPosition.x -= this->playerSpeed;
	}
	this->playerSprite.setPosition(this->playerPosition);
}

void Game::renderenem()
{
	for (auto* enemy : this->enemies)
	{
		enemy->renderEnemy(*this->window);
	}
}

//rendering okna - wyswietlanie obiektów klatka po klatce
void Game::render() {
	this->window->clear(); //Czyszczenie okna
	this->window->draw(this->backgr);
	this->window->draw(this->helpInGame);
	if (this->updateGameState() == 1) {
		this->renderenem();
		this->renderbullet();
		this->renderPlayer();
	}
	else if (this->updateGameState() == 0) {
		this->window->draw(this->gameWon);
	}
	this->window->display(); //Wyświetlenie okna
 }



void Game::renderPlayer()
{
	this->window->draw(this->playerSprite);
}

void Game::renderbullet() {
	for (auto* bullet : this->bullets) {
		bullet->renderBullet(this->window);
	}
}

void Game::isshooting()
{
	if (this->shotCooldown > 0) {
		this->shotCooldown -= 10.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (this->shotCooldown == 0.f) {
			this -> bullets.push_back(new Bullet(&bulletTexture, sf::Vector2f(this->playerPosition.x + 12.f, this->playerPosition.y - 25)));0;
			this->shotCooldown = 500.f;
			std::cout << "isshooting :: BULLET SHOT\n";
		}
	}
}

//koniec klasy Game