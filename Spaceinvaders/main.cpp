//Projekt semestralny gry typu Space Invaders

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
public:
	//Konstruktor
	Game() {
		this->initvar();
		this->initWindow();
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
void Game::initvar() {
	this->window = nullptr; //zainicjowanie pustego wskaŸnika window (nadanie wartoœci NULL)
}

void Game::initWindow() {
	//nadanie rozmiaru okna
	this->videomode.height = 600;
	this->videomode.width = 800;
	//nadanie wskaŸnikowi window rozmiaru okna
	this->window = new sf::RenderWindow(this->videomode, "game_window", sf::Style::Titlebar | sf::Style::Close);
}
//end private metody

void Game::update() {
	//Obs³uga updateowania okna
	this->updatePollEvents();
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

void Game::render() {
	this->window->clear(sf::Color(255, 0, 0, 255)); //Czyszczenie okna
	
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