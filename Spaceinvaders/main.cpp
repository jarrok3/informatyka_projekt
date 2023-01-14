//Projekt semestralny gry typu Space Invaders w ramach przedmiotu Informatyka II
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Game.h"
#include "help.h"
#include "Enemy.h"
#include <ctime>
#include <random>

typedef struct {
    char nazwa[20];
    int liczb_pkt;
    char czas[20];
} gracz_cechy;

int porownaj(const void* left, const void* right) {
    const gracz_cechy* a = (const gracz_cechy*)left;
    const gracz_cechy* b = (const gracz_cechy*)right;
    if (a->liczb_pkt > b->liczb_pkt) {
        return -1;
    }
    else if (a->liczb_pkt < b->liczb_pkt) {
        return 1;
    }
    else {
        return 0;
    }
}
//players to file (uzyte tylko raz dla utworzenia sztucznej bazy graczy)
/*void players_to_file()
{
    srand(time(NULL));
    gracz_cechy playerschar[10];

    FILE* fp;
    fp = fopen("gracze.dat", "w+b");

    strcpy(playerschar[0].nazwa, "Johny");
    strcpy(playerschar[1].nazwa, "Bathman");
    strcpy(playerschar[2].nazwa, "Dedman");
    strcpy(playerschar[3].nazwa, "Bethymanamm");
    strcpy(playerschar[4].nazwa, "Alloy_jr");
    strcpy(playerschar[5].nazwa, "Poul");
    strcpy(playerschar[6].nazwa, "Snake");
    strcpy(playerschar[7].nazwa, "BK");
    strcpy(playerschar[8].nazwa, "Pascal");
    strcpy(playerschar[9].nazwa, "Java");


    for (int i = 0; i < 10; i++)
        playerschar[i].liczb_pkt = rand() % 2000;
    
    fwrite(playerschar, sizeof(gracz_cechy), 10, fp);
    
    fclose(fp);
}
*/

class players_list {
private:
    sf::Text* players;//dane tekstowe do wyswietlenia
    gracz_cechy* player_char;//rzeczywista specyfikacja graczy
    sf::Font czcionka;
    int Np;

    sf::RenderWindow* leaderboard;
    sf::Event ev;

public:
    players_list(int N);
    void laduj();
    void aktualizuj();
    void sortuj();
    void draw(sf::RenderWindow& window);
};

players_list::players_list(int N)
{

    if (!czcionka.loadFromFile("retro.ttf"))
        return;

    FILE* fp = fopen("gracze.dat", "r+b");
    unsigned int rozmiar_plik = 0, ile_graczy = 0;
    fseek(fp, 0, SEEK_END);//na ostatni bajt
    rozmiar_plik = ftell(fp);//czytaj indeks ostatniego bajtu
    ile_graczy = rozmiar_plik / sizeof(gracz_cechy);
    if (N > ile_graczy)
    {
        Np = 5;//moze byc cokolwiek by zabezpieczalo przed odczytem danych ktorych nie ma
    }
    else
    {
        Np = N;
    }

    players = new sf::Text[Np];
    player_char = new gracz_cechy[Np];

    rewind(fp);//czytaj od poczatku
    fread(player_char, sizeof(gracz_cechy), Np, fp);
    fclose(fp);

    for (int i = 0; i < Np; i++)
    {
        players[i].setFont(czcionka);
        players[i].setCharacterSize(30);
        players[i].setFillColor(sf::Color::Red);
        players[i].setPosition(10 + 800 / 4, 20 + i * 50);

    }

    this->leaderboard = new sf::RenderWindow(sf::VideoMode(800, 600), "Leaderboard");
}


void players_list::laduj()
{
    std::string tmp_tekst;
    for (int i = 0; i < Np; i++)
    {
        players[i].setFont(czcionka);
        players[i].setCharacterSize(30);
        players[i].setFillColor(sf::Color::Red);
        players[i].setPosition(10 + 800 / 4, 20 + i * 50);

        tmp_tekst.assign(player_char[i].nazwa);
        tmp_tekst += " Punkty: " + std::to_string(player_char[i].liczb_pkt);
        
        players[i].setString(tmp_tekst);
    }
    
}


void players_list::sortuj()
{
    qsort(player_char, Np, sizeof(gracz_cechy), porownaj);
}

void players_list::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < Np; i++)
    {
        window.draw(players[i]);
    }
}




//START PROGRAMU



int main() {

    //players_to_file();
	// Stwórz window main menu
	sf::RenderWindow window(sf::VideoMode(800, 600), "Main Menu");
	// Nadaj teksture
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background.png"))
		return EXIT_FAILURE;
	sf::Sprite background(backgroundTexture);

	// Stwórz opcje w menu
	sf::Font font;
	if (!font.loadFromFile("retro.ttf"))
		return EXIT_FAILURE;
	sf::Text playOption("Play", font, 50);
	sf::Text leaderboardOption("Leaderboard", font, 50);
	sf::Text exitOption("Exit", font, 50);
    sf::Text helpOption("Help", font, 50);

	playOption.setPosition(200, 100);
	leaderboardOption.setPosition(200, 200);
    helpOption.setPosition(200, 300);
	exitOption.setPosition(200, 400);

	int currentOption = 0;


    while (window.isOpen())
    {
        // Obs³uga eventów
        sf::Event event;

        while (window.pollEvent(event))
        {
            // Zamkniêcie okna manualnie
            if (event.type == sf::Event::Closed)
                window.close();

            //Obs³uga okna Help
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
            {
                help helpWindow;
                while (helpWindow.isrunning()) {

                    //Update okna po zdefiniowaniu event

                    helpWindow.updateEvents();
                    //czyszczenie poprzedniej klatki

                    helpWindow.render();
                    //Wyœwietlenie okna
                }
            }

            // Ruch w górê menu
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            {
                if (currentOption > 0)
                    currentOption--;
            }

            // Ruch w dó³ menu
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            {
                if (currentOption < 3)
                    currentOption++;
            }

            // Wybranie konkretnej opcji menu
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
            {
                if (currentOption == 0)
                {
                    // Rozpoczêcie gry
                    Game game;
                    while (game.isrunning()) {

                        //Update okna po zdefiniowaniu event

                        game.update();
                        //czyszczenie poprzedniej klatki

                        game.render();
                        //Wyœwietlenie okna
                    }
                }
                else if (currentOption == 1)
                {
                    // Otwarcie leaderboardu
                    
                    players_list* pl = new players_list(8);
                    pl->sortuj();
                    pl->laduj();
                    window.clear();
                    pl->draw(window);
                    delete pl;
                }
                else if (currentOption == 2)
                {
                    help helpWindow;
                    while (helpWindow.isrunning()) {

                        //Update okna po zdefiniowaniu event

                        helpWindow.updateEvents();
                        //czyszczenie poprzedniej klatki

                        helpWindow.render();
                        //Wyœwietlenie okna
                    }
                }
                else if (currentOption == 3)
                {
                    // Wyjœcie z gry
                    window.close();
                }
            }
        }

        // Wyczyœæ okno
        window.clear();

        // Narysuj background
        window.draw(background);

        // Narysuj opcje menu
        window.draw(playOption);
        window.draw(leaderboardOption);
        window.draw(exitOption);
        window.draw(helpOption);

        // Podœwietlenie aktualnie wybranej opcji
        if (currentOption == 0)
            playOption.setFillColor(sf::Color::Red);
        else
            playOption.setFillColor(sf::Color::White);

        if (currentOption == 1)
            leaderboardOption.setFillColor(sf::Color::Red);
        else
            leaderboardOption.setFillColor(sf::Color::White);

        if (currentOption == 2)
            helpOption.setFillColor(sf::Color::Red);
        else
            helpOption.setFillColor(sf::Color::White);

        if (currentOption == 3)
            exitOption.setFillColor(sf::Color::Red);
        else
            exitOption.setFillColor(sf::Color::White);

        // Wyœwietl
        window.display();
    }

	return 0;
}