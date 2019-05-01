#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <Windows.h>

extern int X;
extern int Y;
extern int SIZE_OF_TEXTURE;

bool save_score(int sc, int *score)
{
	bool f = false;
	int temp; int temp2; int i = 0;
	for (i ; i < 5; i++)
	{
		if (sc > score[i])
		{ 
			temp = score[i];
			score[i] = sc;
			f = true;
			i++;
			break;
		}
	}
	for (i; i < 5; i++)
	{
		temp2 = score[i];
		score[i] = temp;
		temp = temp2;
	}
	return f;
}

void Game(sf::RenderWindow &window, std::string map_nr, std::string hero_nr, int diff_nr, int *score)
{
	srand(time(NULL));
	sf::Clock clock;
	float timer = 0;
	float delay;
	if (diff_nr == 0)
		delay = 0.15;
	if (diff_nr == 1)
		delay = 0.12;
	if (diff_nr == 2)
		delay = 0.08;

	int a, b;
	bool Game_paused = false;
	bool Game_lose = false;
	bool score_save = false;
	
	//TEXTURES AND TEXT
	sf::Texture t_map, t_krzak;
	sf::Sprite map, krzak;
	t_map.loadFromFile("mapa" + map_nr + ".png", sf::IntRect(0, 0, 20, 20));
	t_krzak.loadFromFile("mapa" + map_nr + ".png", sf::IntRect(20, 0, 20, 20));
	map.setTexture(t_map);
	krzak.setTexture(t_krzak);
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text_score, text_esc, text_pause, text_control, text_w, text_asd, text_pausedgame, text_losedgame, text_savedscore;
	text_score.setFont(font); text_esc.setFont(font); text_pause.setFont(font); text_control.setFont(font); text_pausedgame.setFont(font);
	text_losedgame.setFont(font); text_savedscore.setFont(font);
	text_pause.setString("pause - P"); text_esc.setString("exit - ESC"); text_control.setString("controls - WASD");
	text_pausedgame.setString("GAME PAUSED"); text_losedgame.setString("LOSE!");
	text_score.setCharacterSize(26); text_esc.setCharacterSize(14); text_pause.setCharacterSize(14); text_control.setCharacterSize(14);
	text_pausedgame.setCharacterSize(50); text_losedgame.setCharacterSize(50); text_savedscore.setCharacterSize(20);
	text_score.setFillColor(sf::Color::Yellow);
	text_esc.setFillColor(sf::Color::Yellow);
	text_pause.setFillColor(sf::Color::Yellow);
	text_control.setFillColor(sf::Color::Yellow);
	text_pausedgame.setFillColor(sf::Color::Black);
	text_losedgame.setFillColor(sf::Color::Red);
	text_savedscore.setFillColor(sf::Color::White);
	text_savedscore.setStyle(sf::Text::Underlined);

	//TEXT POSITIONS
	text_score.setPosition(32 * SIZE_OF_TEXTURE, 1 * SIZE_OF_TEXTURE);
	text_esc.setPosition(32 * SIZE_OF_TEXTURE, 10 * SIZE_OF_TEXTURE);
	text_pause.setPosition(32 * SIZE_OF_TEXTURE, 11 * SIZE_OF_TEXTURE);
	text_control.setPosition(32 * SIZE_OF_TEXTURE, 12 * SIZE_OF_TEXTURE);
	text_pausedgame.setPosition(7 * SIZE_OF_TEXTURE, 13 * SIZE_OF_TEXTURE);
	text_losedgame.setPosition(11 * SIZE_OF_TEXTURE, 13 * SIZE_OF_TEXTURE);
	text_savedscore.setPosition(12 * SIZE_OF_TEXTURE, 16 * SIZE_OF_TEXTURE);

	
	sf::Texture t_tlo;
	t_tlo.loadFromFile("tlo.png");
	sf::Sprite tlo(t_tlo);
	tlo.setPosition(0, 0);

	//OBJECTS
	Snake snek(5, hero_nr);
	Fruct f(map_nr);

	while (window.isOpen())
	{
		
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;										//Game's clock

		//INPUTS
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				return;
			if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::Escape)
			{
				score_save = save_score(snek.score, score);
				if (score_save == true)
				{
					text_savedscore.setString("Saved score: "+std::to_string(snek.score));
					window.draw(text_savedscore);
					window.display();
					Sleep(2000);
				}
				return;
			}
			if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::P && Game_paused == false)
				Game_paused = true;
			else if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::P && Game_paused == true)
				Game_paused = false;
		}

		if (Game_paused == false)
		{
			if (snek.colision())
				Game_lose = true;
			snek.get_move();
			//GAME FRAME
			if (timer > delay)
			{
				timer = 0;
				snek.set_position();
				if (f.collected(snek.get_head_X(), snek.get_head_Y()))
				{
					a = rand() % (X - 3) + 1;
					b = rand() % (Y - 3) + 1;
					f.set_position(a, b);
					snek.grow();
				}
			}
		}
		
		//DRAW
		window.clear(sf::Color::Black);
		window.draw(tlo);
		for (int i = 0; i < X; i++)
			for (int j = 0; j < Y; j++)
			{
				map.setPosition(i*SIZE_OF_TEXTURE, j*SIZE_OF_TEXTURE); window.draw(map);
				if (i == 0 || j == 0 || i == X - 1 || j == Y - 1)
					krzak.setPosition(i*SIZE_OF_TEXTURE, j*SIZE_OF_TEXTURE); window.draw(krzak);
			}
		//legend
		text_score.setString("Score: "+std::to_string(snek.score));
		window.draw(text_score);
		window.draw(text_esc);
		window.draw(text_pause);
		window.draw(text_control);

		f.draw(window);
		snek.draw(window);
		if (Game_paused == true)
		{
			window.draw(text_pausedgame);
		}
		if (Game_lose == true)
		{
			score_save = save_score(snek.score, score);
			clock.restart();
			while (true)
			{
				time = clock.getElapsedTime().asSeconds();
				timer = 0; timer += time;
				if (score_save == true)
				{
					text_savedscore.setString("Saved score: " + std::to_string(snek.score));
					window.draw(text_savedscore);
				}
				window.draw(text_losedgame);
				window.display();
				if (timer > 2) return;
			}
		}
		window.display();
	}
}