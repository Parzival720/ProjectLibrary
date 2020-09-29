#pragma once

#include "Project.h"
#include "TextBox.h"

/*
	Class: Snake
		A class containing the UI and logic to run a game of snake. 
		
		Extends the Project abstract class.

	Level 1 - Can Pass through Walls
	Level 2 - Bounce off Walls, Avoid Rocks
	Level 3 - Die if hit walls, rocks or self
	Level 4 - Die if hit walls, rocks or self

	Collectables:
		Apple - food item that increases score and length of snake
		Rock - Obstacle that kills the snake
		Wormhole - Teleports the Snake to a random space on the map
*/

// All Constants defining Size and number of collectables per level
const int BOARD_SIZE = 400;
const int START_SCORE = 3;
const int X_MAX = 23;
const int Y_MAX = 22;

const int MAX_SNAKE = 128;
const int MAX_FOOD = 10;
const int MAX_ROCK = 5;
const int OBJECT_SIZE = 15;

const int LEVEL_1_FOOD = MAX_FOOD;
const int LEVEL_2_FOOD = MAX_FOOD;
const int LEVEL_3_FOOD = 1;
const int LEVEL_4_FOOD = 1;

// Movement constants
enum DIRECTION { RIGHT, UP, LEFT, DOWN };
// Game States
enum MODE { IDLE, SETUP, PLAY, NEXT, EOG };

// Coordinate Struct
struct POINT
{
	int x;
	int y;
};

// Snake Segment Object
struct SNAKE
{
	POINT point;
};

// General Object for all Collectables: Food, Rocks, and Wormhole
struct COLLECTABLE
{
	union
	{
		POINT point;
	} collectable_loc;
	int size;
	int value;
};

const std::string arialFile = "arial.ttf";
class Snake : public Project
{
public:
	Snake(float screenHeight, float screenWidth);

	Project* executeEvent(sf::Event event, sf::RenderWindow& window);

	std::string getName() const { return "Snake"; };

// All UI Functions and variables
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::ConvexShape backgroundShape;
	sf::ConvexShape gameWindow;

	TextBox startButton;
	TextBox exitButton;

	sf::Font arial;
	sf::Text gameOverWriter;

	sf::Texture vortexPic;
	sf::Texture grassBackground;
	sf::Texture applePic;
	sf::Texture rockPic;
	sf::Texture snakeHeadPic;
	sf::Texture snakeBodyPic;
	sf::Texture snakeTailPic;

	float screenHeight;
	float screenWidth;

// All Game Logic functions and variables
private:
	void newGame();
	void startLevel();
	void nextLevel();
	void endGame();

	int isFood(POINT p);
	int isRock(POINT p);
	int isWorm(POINT p);
	int isSnake(POINT p);

	int COL(int x) const;
	int ROW(int y) const;

	COLLECTABLE* newItem(int x, int y, int value, int size);

	void addHead(int* head, int* direction);
	void moveSnake();
	void turnRight();
	void turnLeft();
	void turnUp();
	void turnDown();

	int start_x;
	int start_y;

	enum MODE game_mode;
	int score;
	int level;
	int direction;
	int head;
	int tail;
	int eaten;

	SNAKE snake[MAX_SNAKE];
	COLLECTABLE* food[MAX_FOOD];
	COLLECTABLE* rocks[MAX_ROCK];
	COLLECTABLE* wormhole;
};