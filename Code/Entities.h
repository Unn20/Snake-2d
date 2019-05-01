#include <SFML\Graphics.hpp>



class Snake
{
	sf::Texture t_head1, t_head2, t_body1, t_body2, t_tail, t_connect;	//textures
	sf::Sprite head1, head2, body1, body2, tail, connect;				//sprites
	struct snake_square
	{
		int x, y;							//position
		int angle;							//angle of square; 0-N;1-E;2-S;3-W
	} s[300];								//max length of snake[300]
	int length;								//lentgh of a snake
	int direction;							//0-NORTH;1-EAST;2-SOUTH;3-WEST
	int size;								//size of a texture
	int tick;								//for tongue texture
public:
	int score;								//score

	Snake();								//snake length 15 with NO texture !! ONLY FOR MENU !!
	Snake(int l, std::string snake_nr);		//l=length of snake ; snake_nr - texture
	~Snake();
	int get_head_X();						//get x coordinate of snake's head
	int get_head_Y();						//get y coordinate od snake's head
	void get_move();						//function that get keyboard input to change direction
	void set_position();					//set position of whole snake in one game tick"
	void draw(sf::RenderWindow &window);	//draw snake
	void grow();							//incrementating snake
	bool colision();						//true if there is collision
	bool snake_colision(int x, int y);		//check if (x,y) on snake

	void set_texture(int nr);					//FOR MENU
	void menu_set_postion();					//FOR MENU
	void menu_draw(sf::RenderWindow &window);	//FOR MENU
};


class Fruct
{
	sf::Texture t_fruct;					//fruct texture
	sf::Sprite fr;							//sprite
	int x, y;								//position
public:
	Fruct();								//FOR MENU
	Fruct(std::string nr);							//texture
	~Fruct();
	int get_X();								//get x coordinate
	int get_Y();								//get y coordinate
	void set_position(int a, int b);			//set position (x,y) of fruct
	void draw(sf::RenderWindow &window);		//draw a fruct
	bool collected(int a, int b);				//check if snake got a fruct

	void set_texture(int nr);					//FOR MENU
	void menu_draw(sf::RenderWindow &window);	//FOR MENU
};