//Projekt semestralny gry typu Space Invaders w ramach przedmiotu Informatyka II

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>

class Game{
private:
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	void initvar();
	void initWindow();

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

//private metody
void Game::initgracz() {
	if (!teksturagr.loadFromFile("player.png")) {
		std::cout << "Failed to load image";
		return;
	}
	this->teksturagr.loadFromFile("player.png");
	this->player.setTexture(teksturagr);
	this->player.scale(0.2f, 0.2f);
	this->player.setPosition(this->videomode.width/2, 500);
}
void Game::initpauz(){
	if (!teksturapauz.loadFromFile("pause-button.png")) {
		std::cout << "Failed to load image";
		return;
	}
	this->teksturapauz.loadFromFile("pause-button.png");
	this->pauza.setTexture(teksturapauz);
	this->pauza.scale(0.1f, 0.1f);
	this->pauza.setPosition(this->videomode.width - 60, 10);
}
void Game::initenem() {
	if (!teksturaenem.loadFromFile("enemy.png")) {
		std::cout << "Failed to load image";
		return;
	}
	this->teksturaenem.loadFromFile("enemy.png");
	this->enemy.setTexture(teksturaenem);
	this->enemy.scale(0.3f, 0.3f);
	this->enemy.setPosition( 15, 10);
}

void Game::initvar() {
	this->window = nullptr; //zainicjowanie pustego wskaŸnika window (nadanie wartoœci NULL)
}

void Game::initWindow() {
	//nadanie rozmiaru okna
	this->videomode.height = 600;
	this->videomode.width = 800;
	//nadanie wskaŸnikowi window rozmiaru okna
	this->window = new sf::RenderWindow(this->videomode, "Ala Space Invaders", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}
//end private metody

void Game::update() {
	//Obs³uga aktualizowania okna (zale¿nie od wydarzeñ)
	this->updatePollEvents();

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
			if (ev.key.code == sf::Keyboard::Escape) this->window->close();
			break;
		}
	}
}

//rendering okna - wyswietlanie obiektów klatka po klatce
void Game::render() {
	this->window->clear(); //Czyszczenie okna
	this->window->draw(this->player);
	this->window->draw(this->pauza);
	this->window->draw(this->enemy);
	this->window->display(); //Wyœwietlenie okna
}
//koniec klasy Game

int main() {

	Game game;

	//Pêtla dzia³ania gry
	while (game.isrunning()) {
		
		
		//Update okna po zdefiniowaniu event

		game.update();
		
		
		//czyszczenie poprzedniej klatki

		game.render();

		 

		 //Wyœwietlenie okna
	}
	//Koniec programu
	return 0;
}