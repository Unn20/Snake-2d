#include <SFML\Graphics.hpp>
#include "Game_menu.h"

/*
Maciej Leszczyk 136759
Informatyka I2, semestr 2,
Gra jest projektem na zaliczenie przedmiotu Programowania Niskopoziomowego
*/

int X = 30;
int Y = 30;
int SIZE_OF_TEXTURE = 20;

int main()
{
	sf::RenderWindow window(sf::VideoMode((X+10)*SIZE_OF_TEXTURE, (Y)*SIZE_OF_TEXTURE), "SNAKE", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	Game_menu(window);
	return EXIT_SUCCESS;
}