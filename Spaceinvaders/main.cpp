//Projekt semestralny gry typu Space Invaders w ramach przedmiotu Informatyka II

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Game.h"
#include "help.h"
#include "Enemy.h"

int main() {

	// Stw�rz window main menu
	sf::RenderWindow window(sf::VideoMode(800, 600), "Main Menu");

	// Nadaj teksture
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background.png"))
		return EXIT_FAILURE;
	sf::Sprite background(backgroundTexture);

	// Stw�rz opcje w menu
	sf::Font font;
	if (!font.loadFromFile("retro.ttf"))
		return EXIT_FAILURE;
	sf::Text playOption("Play", font, 50);
	sf::Text leaderboardOption("Leaderboard", font, 50);
	sf::Text exitOption("Exit", font, 50);

	playOption.setPosition(200, 100);
	leaderboardOption.setPosition(200, 200);
	exitOption.setPosition(200, 300);

	int currentOption = 0;


    while (window.isOpen())
    {
        // Obs�uga event�w
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Zamkni�cie okna manualnie
            if (event.type == sf::Event::Closed)
                window.close();

            //Obs�uga okna Help
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
            {
                help helpWindow;
                while (helpWindow.isrunning()) {

                    //Update okna po zdefiniowaniu event

                    helpWindow.updateEvents();
                    //czyszczenie poprzedniej klatki

                    helpWindow.render();
                    //Wy�wietlenie okna
                }
            }

            // Ruch w g�r� menu
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            {
                if (currentOption > 0)
                    currentOption--;
            }

            // Ruch w d� menu
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            {
                if (currentOption < 2)
                    currentOption++;
            }

            // Wybranie konkretnej opcji menu
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
            {
                if (currentOption == 0)
                {
                    // Rozpocz�cie gry
                    Game game;
                    while (game.isrunning()) {

                        //Update okna po zdefiniowaniu event

                        game.update();
                        //czyszczenie poprzedniej klatki

                        game.render();
                        //Wy�wietlenie okna
                    }
                }
                else if (currentOption == 1)
                {
                    // Otwarcie leaderboardu
                }
                else if (currentOption == 2)
                {
                    // Wyj�cie z gry
                    window.close();
                }
            }
        }

        // Wyczy�� okno
        window.clear();

        // Narysuj background
        window.draw(background);

        // Narysuj opcje menu
        window.draw(playOption);
        window.draw(leaderboardOption);
        window.draw(exitOption);

        // Pod�wietlenie aktualnie wybranej opcji
        if (currentOption == 0)
            playOption.setFillColor(sf::Color::Red);
        else
            playOption.setFillColor(sf::Color::White);

        if (currentOption == 1)
            leaderboardOption.setFillColor(sf::Color::Red);
        else
            leaderboardOption.setFillColor(sf::Color::White);

        if (currentOption == 2)
            exitOption.setFillColor(sf::Color::Red);
        else
            exitOption.setFillColor(sf::Color::White);

        // Wy�wietl
        window.display();
    }

	return 0;
}