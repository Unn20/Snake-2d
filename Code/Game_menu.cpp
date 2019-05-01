#include "Game_menu.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

void Game_menu(sf::RenderWindow &window)
{
	int choice = 0;

	//SETTINGS
	std::string text_temp;
	int maps, heroes;
	std::ifstream f_settings;
	f_settings.open("settings.txt");
	f_settings >> text_temp;
	f_settings >> maps;
	f_settings >> text_temp;
	f_settings >> heroes;

	//SCORE FILE
	std::ifstream fs_score;
	std::ofstream f_score;
	fs_score.open("score.txt");
	int score[5];
	for (int i = 0; i < 5; i++)
	{
		fs_score >> score[i];
		if (score[i] < 0) score[i] = 1;
	}
	f_score.open("score.txt");

	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Texture t_tytul;
	t_tytul.loadFromFile("tytul.png", sf::IntRect(0,0,300,120));
	sf::Sprite tytul(t_tytul);

	sf::Texture t_tlo;
	t_tlo.loadFromFile("tlo.png");
	sf::Sprite tlo(t_tlo);
	tlo.setPosition(0, 0);

	sf::Color menu_color(180, 221, 107);

	sf::Text menu1, menu2, menu3;
	menu1.setFont(font); menu2.setFont(font); menu3.setFont(font);
	menu1.setCharacterSize(24); menu2.setCharacterSize(24); menu3.setCharacterSize(24);
	menu1.setString("Play"); menu2.setString("Highscores"); menu3.setString("Exit");
	menu1.setFillColor(sf::Color::Red); menu2.setFillColor(sf::Color::Red); menu3.setFillColor(sf::Color::Red);
	menu1.setStyle(sf::Text::Bold | sf::Text::Underlined);
	menu2.setStyle(sf::Text::Bold | sf::Text::Underlined);
	menu3.setStyle(sf::Text::Bold | sf::Text::Underlined);

	tytul.setPosition(200, 50);
	menu1.setPosition(250, 200);
	menu2.setPosition(250, 250);
	menu3.setPosition(250, 300);

	sf::RectangleShape rectliner;
	sf::RectangleShape rectrectliner;
	rectliner.setFillColor(sf::Color::Blue);
	rectrectliner.setFillColor(sf::Color::Magenta);
	rectliner.setSize(sf::Vector2f(298, 48));
	rectrectliner.setSize(sf::Vector2f(300, 50));

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				f_score.close();
				fs_score.close();
				window.close();
			}
			if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::W && choice != 0)
			{
				choice--;
			}
			if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::S && choice != 2)
			{
				choice++;
			}
			if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::Return)
			{
				switch (choice)
				{
				case 0:
					Game_choose(window, score, maps, heroes);
					break;
				case 1:
					Highscores(window, score);
					break;
				case 2:
					for (int i = 0; i < 5; i++)
						f_score << score[i] << std::endl;
					f_score.close();
					fs_score.close();
					return;
					break;
				}
			}
		}
	
		
		rectliner.setPosition(sf::Vector2f(201, choice * 50 + 201));
		rectrectliner.setPosition(sf::Vector2f(200, choice * 50 + 200));
		//DRAW
		window.clear(menu_color);
		window.draw(tlo);
		window.draw(rectrectliner);
		window.draw(rectliner);
		window.draw(tytul);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();
	}
}


void Game_choose(sf::RenderWindow &window,int *scores, int maps, int heroes)
{
	int choice = 0, map_choice = 0, hero_choice = 0, diff_choice = 0;

	//TEXT
	sf::Color menu_color(180, 221, 107);
	sf::Text option1, option2, option3, option4, info, map_number, heroes_number;
	sf::Font font;
	font.loadFromFile("arial.ttf");
	option1.setFont(font); option2.setFont(font); option3.setFont(font); option4.setFont(font);
	info.setFont(font); map_number.setFont(font); heroes_number.setFont(font);
	option1.setString("Start game"); option3.setString("< Choose map: >");
	option4.setString("< Choose hero: >");
	info.setString("Press Esc to return");
	map_number.setString("Maps avalible: " + std::to_string(maps)); heroes_number.setString("Heroes avalible: " + std::to_string(heroes));
	map_number.setFillColor(sf::Color::Blue); heroes_number.setFillColor(sf::Color::Blue);
	option1.setFillColor(sf::Color::Red); option2.setFillColor(sf::Color::Red); option3.setFillColor(sf::Color::Red); 
	option4.setFillColor(sf::Color::Red); info.setFillColor(sf::Color::Red);
	option1.setCharacterSize(20); option2.setCharacterSize(20); option3.setCharacterSize(20); option4.setCharacterSize(20);
	info.setCharacterSize(12); map_number.setCharacterSize(15); heroes_number.setCharacterSize(15);
	option1.setPosition(200, 200); option2.setPosition(200, 250); option3.setPosition(200, 300); option4.setPosition(200, 350); info.setPosition(300, 500);
	map_number.setPosition(100, 50); heroes_number.setPosition(100, 80);

	
	//RECTANGLES
	sf::RectangleShape rectliner;
	sf::RectangleShape rectrectliner;
	rectliner.setFillColor(sf::Color::Blue);
	rectrectliner.setFillColor(sf::Color::Magenta);
	rectliner.setSize(sf::Vector2f(298, 48));
	rectrectliner.setSize(sf::Vector2f(300, 50));

	sf::Texture t_tlo;
	t_tlo.loadFromFile("tlo.png");
	sf::Sprite tlo(t_tlo);
	tlo.setPosition(0, 0);

	//TEXTURES
	//maps
	sf::Texture t_map[10], t_krzak[10];
	sf::Sprite map[10], krzak[10];
	for (int i = 0; i < maps; i++)
	{
		t_map[i].loadFromFile("mapa" + std::to_string(i) + ".png", sf::IntRect(0, 0, 20, 20));
		map[i].setTexture(t_map[i]);
		t_krzak[i].loadFromFile("mapa" + std::to_string(i) + ".png", sf::IntRect(20, 0, 20, 20));
		krzak[i].setTexture(t_krzak[i]);
	}
	//fructs
	Fruct fructs[10*8];
	for (int i = 0; i < 8*maps; i++)
	{
		fructs[i].set_texture(floor(i/8));
		if (i % 8 == 0)
			fructs[i].set_position(520,120);
		else if (i % 8 == 1)
			fructs[i].set_position(550,180);
		else if (i % 8 == 2)
			fructs[i].set_position(550,335);
		else if (i % 8 == 3)
			fructs[i].set_position(520,470);
		else if (i % 8 == 4)
			fructs[i].set_position(625,250);
		else if (i % 8 == 5)
			fructs[i].set_position(680,260);
		else if (i % 8 == 6)
			fructs[i].set_position(640,400);
		else if (i % 8 == 7)
			fructs[i].set_position(640,450);
	}
	
	//SNAKE
	Snake snek[10];
	for (int i = 0; i < heroes; i++)
	{
		snek[i].set_texture(i);
	}

	//TIMER
	sf::Clock clock;
	float timer = 0;

	while (window.isOpen())
	{
		float delay;
		//difficulity
		if (diff_choice == 0)
			delay = 0.15;
		if (diff_choice == 1)
			delay = 0.12;
		if (diff_choice == 2)
			delay = 0.08;
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//INPUT
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				return;
			if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::Escape)
			{
				return;
			}
			if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::W && choice != 0)
			{
				choice--;
			}
			if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::S && choice != 3)
			{
				choice++;
			}
			if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::Return)
			{
				switch (choice)
				{
				case 0:
					Game(window, std::to_string(map_choice), std::to_string(hero_choice), diff_choice, scores);
					break;
				default:
					break;
				}
			}
			if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::A)
			{
				switch (choice)
				{
				case 1:
					if (diff_choice != 0)
						diff_choice--;
					break;
				case 2:
					if (map_choice != 0)
						map_choice--;
					break;
				case 3:
					if (hero_choice != 0)
						hero_choice--;
					break;
				default:
					break;
				}
			}
			if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::D)
			{
				switch (choice)
				{
				case 1:
					if (diff_choice != 2)
						diff_choice++;
					break;
				case 2:
					if (map_choice != maps - 1)
						map_choice++;
					break;
				case 3:
					if (hero_choice != heroes - 1)
						hero_choice++;
					break;
				default:
					break;
				}
			}

		}

		if (timer > delay)
		{
			timer = 0;
			snek[hero_choice].menu_set_postion();
		}

		rectliner.setPosition(sf::Vector2f(151, choice * 50 + 201));
		rectrectliner.setPosition(sf::Vector2f(150, choice * 50 + 200));
		
		option2.setString("< Choose speed: > " + std::to_string(diff_choice));


		//DRAW
		window.clear(menu_color);
		window.draw(tlo);
		for(int a = 500; a<=700; a+=20)
			for (int b = 100; b <= 500; b += 20)
			{
				map[map_choice].setPosition(a, b);
				window.draw(map[map_choice]);
				if (a == 500 || b == 100 || a == 700 || b == 500)
				{
					krzak[map_choice].setPosition(a,b);
					window.draw(krzak[map_choice]);
				}
			}
		snek[hero_choice].menu_draw(window);
		for (int i = map_choice * 8; i < map_choice * 8 + 8; i++)
		{
			fructs[i].menu_draw(window);
		}

		window.draw(rectrectliner);
		window.draw(rectliner);
		window.draw(map_number);
		window.draw(heroes_number);
		window.draw(option1);
		window.draw(option2);
		window.draw(option3);
		window.draw(option4);
		window.draw(info);
		window.display();
	}



}

void Highscores(sf::RenderWindow &window, int *scores)
{
	//TEXT TEXTURES
	sf::Text title, text_score[5], info;
	sf::Font font;
	font.loadFromFile("arial.ttf");
	std::string places[5];
	places[0] = "I  "; places[1] = "II "; places[2] = "III"; places[3] = "IV"; places[4] = "V ";
	sf::Color menu_color(180, 221, 107);
	title.setFont(font); info.setFont(font);
	title.setString("HIGHSCORES"); info.setString("Press Esc to return");
	title.setFillColor(sf::Color::Red); info.setFillColor(sf::Color::Red);
	title.setStyle(sf::Text::Bold | sf::Text::Underlined);
	title.setCharacterSize(50); info.setCharacterSize(12);
	title.setPosition(200,50); info.setPosition(300,500);
	for (int i = 0; i < 5; i++)
	{
		text_score[i].setFont(font);
		text_score[i].setString(places[i] + ".\t\t" + std::to_string(scores[i])+" points");
		text_score[i].setFillColor(sf::Color::Red);
		text_score[i].setCharacterSize(16);
		text_score[i].setPosition(150,i*30+200);
	}

	//RECTANGLES
	sf::RectangleShape rectliner;
	sf::RectangleShape rectrectliner;
	rectliner.setFillColor(menu_color);
	rectrectliner.setFillColor(sf::Color::Magenta);
	rectliner.setSize(sf::Vector2f(298, 198));
	rectrectliner.setSize(sf::Vector2f(300, 200));
	rectliner.setPosition(126, 166);
	rectrectliner.setPosition(125, 165);


	sf::Texture t_tlo;
	t_tlo.loadFromFile("tlo.png");
	sf::Sprite tlo(t_tlo);
	tlo.setPosition(0, 0);

	while (window.isOpen())
	{
		//INPUT
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				return;
			if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::Escape)
			{
				return;
			}
		}
		//DRAW
		window.clear(menu_color);
		window.draw(tlo);
		window.draw(rectrectliner);
		window.draw(rectliner);
		window.draw(title);
		window.draw(info);
		for (int i = 0; i < 5; i++)
		{
			window.draw(text_score[i]);
		}
		window.display();
	}
}