#include "Entities.h"
#include <cstdlib>
#include <iostream>

extern int X;
extern int Y;
extern int SIZE_OF_TEXTURE;

Snake::Snake()
{
	score = 0;
	length = 15;
	direction = 2;
	size = SIZE_OF_TEXTURE;
	tick = 0;
	s[0].x = 31;						//Starting..
	s[0].y = 23;						//..location
	s[0].angle = 2;						//direction SOUTH
	for (int i = 1; i <= 15; i++)
	{
		s[i].x = s[0].x;
		s[i].y = s[0].y - i;
		s[i].angle = 2;
	}
}

void Snake::set_texture(int nr)
{
	std::string numbr = std::to_string(nr);
	t_body1.loadFromFile("snake_teksture" + numbr + ".png", sf::IntRect(0, 0, 20, 20));
	t_body2.loadFromFile("snake_teksture" + numbr + ".png", sf::IntRect(20, 0, 20, 20));
	t_head1.loadFromFile("snake_teksture" + numbr + ".png", sf::IntRect(40, 0, 20, 20));
	t_head2.loadFromFile("snake_teksture" + numbr + ".png", sf::IntRect(60, 0, 20, 20));
	t_tail.loadFromFile("snake_teksture" + numbr + ".png", sf::IntRect(80, 0, 20, 20));
	t_connect.loadFromFile("snake_teksture" + numbr + ".png", sf::IntRect(100, 0, 20, 20));
	head1.setTexture(t_head1); head1.setOrigin(sf::Vector2f(10, 10));
	head2.setTexture(t_head2); head2.setOrigin(sf::Vector2f(10, 10));
	body1.setTexture(t_body1); body1.setOrigin(sf::Vector2f(10, 10));
	body2.setTexture(t_body2); body2.setOrigin(sf::Vector2f(10, 10));
	tail.setTexture(t_tail); tail.setOrigin(sf::Vector2f(10, 10));
	connect.setTexture(t_connect); connect.setOrigin(sf::Vector2f(10, 10));
}




Snake::Snake(int l,std::string snake_nr)
{						//TEXTURES
	t_body1.loadFromFile("snake_teksture" + snake_nr + ".png", sf::IntRect(0, 0, 20, 20));
	t_body2.loadFromFile("snake_teksture" + snake_nr + ".png", sf::IntRect(20, 0, 20, 20));
	t_head1.loadFromFile("snake_teksture" + snake_nr + ".png", sf::IntRect(40, 0, 20, 20));
	t_head2.loadFromFile("snake_teksture" + snake_nr + ".png", sf::IntRect(60, 0, 20, 20));
	t_tail.loadFromFile("snake_teksture" + snake_nr + ".png", sf::IntRect(80, 0, 20, 20));
	t_connect.loadFromFile("snake_teksture" + snake_nr + ".png", sf::IntRect(100, 0, 20, 20));
	head1.setTexture(t_head1); head1.setOrigin(sf::Vector2f(10, 10));
	head2.setTexture(t_head2); head2.setOrigin(sf::Vector2f(10, 10));
	body1.setTexture(t_body1); body1.setOrigin(sf::Vector2f(10, 10));
	body2.setTexture(t_body2); body2.setOrigin(sf::Vector2f(10, 10));
	tail.setTexture(t_tail); tail.setOrigin(sf::Vector2f(10, 10));
	connect.setTexture(t_connect); connect.setOrigin(sf::Vector2f(10, 10));
						//
	score = 0;
	length = l;
	direction = 2;
	size = SIZE_OF_TEXTURE;
	tick = 0;
	s[0].x = (rand() % 20)+5;			//Starting..
	s[0].y = (rand() % 10)+5;			//..location
	s[0].angle = 2;						//direction SOUTH
	for (int i = 1; i <=l; i++)
	{
		s[i].x = s[0].x;
		s[i].y = s[0].y - i;
		s[i].angle = 2;
	}
	
}

Snake::~Snake(){}

int Snake::get_head_X()
{
	return s[0].x - 1 ;
}
int Snake::get_head_Y()
{
	return s[0].y - 1;
}

void Snake::get_move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (s[1].y != s[0].y - 1)) { direction = 0; return; }	//NORTH
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (s[1].x != s[0].x + 1)) { direction = 1; return; }	//EAST
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (s[1].y != s[0].y + 1)) { direction = 2; return; }	//SOUTH
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (s[1].x != s[0].x - 1)) { direction = 3; return; }	//WEST
}

void Snake::set_position()
{
	for (int i = length; i > 0; i--)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
		s[i].angle = s[i - 1].angle;
	}
	if (direction == 0) { s[0].y -= 1; s[0].angle = 0; }
	if (direction == 1) { s[0].x += 1; s[0].angle = 1; }
	if (direction == 2) { s[0].y += 1; s[0].angle = 2; }
	if (direction == 3) { s[0].x -= 1; s[0].angle = 3; }

	if (tick == 0) tick = 1;
	else tick = 0;
}

void Snake::menu_set_postion()
{
	if (tick == 0) tick = 1;
	else tick = 0;
}

void Snake::menu_draw(sf::RenderWindow &window)
{
	for (int i = 0; i <= length; i++)
	{
		if (i == 0)
		{
			if (tick == 0)
			{
				head1.setPosition(s[i].x*size - 10, s[i].y*size - 10);
				head1.setRotation(s[i].angle * 90);
				window.draw(head1);
			}
			if (tick == 1)
			{
				head2.setPosition(s[i].x*size - 10, s[i].y*size - 10);
				head2.setRotation(s[i].angle * 90);
				window.draw(head2);
			}

		}
		if (i == length)		//TAIL
		{
			tail.setPosition(s[i].x*size - 10, s[i].y*size - 10);
			tail.setRotation(s[i - 1].angle * 90 + 180);
			window.draw(tail);
		}
		if (i != 0 && i != length)		//REST OF SNAKE BODY
		{
			if (tick % 2 == 0)
			{
				body1.setPosition(s[i].x*size - 10, s[i].y*size - 10);
				body1.setRotation(s[i].angle * 90);
				window.draw(body1);
			}
			else
			{
				body2.setPosition(s[i].x*size - 10, s[i].y*size - 10);
				body2.setRotation(s[i].angle * 90);
				window.draw(body2);
			}
		}
	}
}


void Snake::draw(sf::RenderWindow &window)
{
	for (int i = 0; i <= length; i++)		//HEAD
	{
		if (i == 0)
		{
			if (tick == 0)
			{
				head1.setPosition(s[i].x*size-10, s[i].y*size-10);
				head1.setRotation(s[i].angle * 90);
				window.draw(head1);
			}
			if (tick == 1)
			{
				head2.setPosition(s[i].x*size-10, s[i].y*size-10);
				head2.setRotation(s[i].angle * 90);
				window.draw(head2);
			}
		}

		if (i == length)		//TAIL
		{ 
			tail.setPosition(s[i].x*size-10, s[i].y*size-10); 
			tail.setRotation(s[i-1].angle*90+180);
			window.draw(tail);
		}
		
		if (i!=0 && i!=length)		//REST OF SNAKE BODY
		{
			if (!((s[i].x == s[i - 1].x && s[i].x == s[i + 1].x) || (s[i].y == s[i - 1].y && s[i].y == s[i + 1].y)))	//connector
			{
				connect.setPosition(s[i].x*size - 10, s[i].y*size - 10);
				if ((s[i].x == s[i - 1].x - 1 && s[i].y == s[i + 1].y + 1) || (s[i].y == s[i - 1].y + 1 && s[i].x == s[i + 1].x - 1))
					connect.setRotation(270);
				if ((s[i].x == s[i - 1].x + 1 && s[i].y == s[i + 1].y - 1) || (s[i].y == s[i - 1].y - 1 && s[i].x == s[i + 1].x + 1))
					connect.setRotation(90);
				if ((s[i].x == s[i - 1].x + 1 && s[i].y == s[i + 1].y + 1) || (s[i].y == s[i - 1].y + 1 && s[i].x == s[i + 1].x + 1))
					connect.setRotation(180);
				if ((s[i].x == s[i - 1].x - 1 && s[i].y == s[i + 1].y - 1) || (s[i].y == s[i - 1].y - 1 && s[i].x == s[i + 1].x - 1))
					connect.setRotation(0);
				window.draw(connect);
			}
			else
			{
				if (i % 2 == 0)
				{
					body1.setPosition(s[i].x*size - 10, s[i].y*size - 10);
					body1.setRotation(s[i].angle * 90);
					window.draw(body1);
				}
				else
				{
					body2.setPosition(s[i].x*size - 10, s[i].y*size - 10);
					body2.setRotation(s[i].angle * 90);
					window.draw(body2);
				}
			}
		}
	}
}

void Snake::grow()
{
	length++;
	score++;
}

bool Snake::colision()
{
	//game borders collision
	if ((get_head_X() <= 0) || (get_head_X() >= X-1)) return true;
	if ((get_head_Y() <= 0) || (get_head_Y() >= Y-1)) return true;
	//snake collision
	for (int i = length; i > 3; i--)
	{
		if (s[0].x == s[i].x && s[0].y == s[i].y) return true;
	}
	return false;
}

bool Snake::snake_colision(int x, int y)
{
	for (int i = 0; i <= length; i++)
	{
		if (x == s[i].x && y == s[i].y) return true;
	}
	return false;
}

//FRUCT

Fruct::Fruct()
{
	t_fruct.loadFromFile("mapa0.png", sf::IntRect(40, 0, 20, 20));
	fr.setTexture(t_fruct);
	x = 100;
	y = 100;
}

Fruct::Fruct(std::string nr)
{
	t_fruct.loadFromFile("mapa"+nr+".png", sf::IntRect(40, 0, 20, 20));
	fr.setTexture(t_fruct);
	x = rand() % (X-2) + 1;
	y = rand() % (Y-2) + 1;
}

void Fruct::set_texture(int nr)
{
	std::string text_nr = std::to_string(nr);
	t_fruct.loadFromFile("mapa" + text_nr + ".png", sf::IntRect(40, 0, 20, 20));
	fr.setTexture(t_fruct);
}

Fruct::~Fruct() {}

int Fruct::get_X()
{
	return x;
}
int Fruct::get_Y()
{
	return y;
}

void Fruct::set_position(int a, int b)
{
	x = a;
	y = b;
}

void Fruct::draw(sf::RenderWindow &window)
{
	fr.setPosition(x*SIZE_OF_TEXTURE, y*SIZE_OF_TEXTURE);
	window.draw(fr);
}

void Fruct::menu_draw(sf::RenderWindow &window)
{
	fr.setPosition(x, y);
	window.draw(fr);
}

bool Fruct::collected(int a, int b)
{
	if (a == x && b == y) return true;
	else return false;
}