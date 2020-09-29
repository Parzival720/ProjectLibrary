#include "Snake.h"
#include "Menu.h"

/*
   Constructor
   Sets up the Snake Game Screen and initializes all Textures. 
   parameters:
	  screenHeight - the current Height of the Screen
	  screenWidth - the current Width of the Screen
*/
Snake::Snake(float screenHeight, float screenWidth) 
{
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	start_x = screenWidth / 5;
	start_y = screenHeight / 6 - 50;

	// Create the Background Shape
	backgroundShape.setPointCount(5);
	backgroundShape.setFillColor(sf::Color(0, 255, 0));
	backgroundShape.setOutlineThickness(3.0f);
	backgroundShape.setOutlineColor(sf::Color::White);

	backgroundShape.setPoint(0, sf::Vector2f(0.0f, 0.0f));
	backgroundShape.setPoint(1, sf::Vector2f(screenWidth, 0.0f));
	backgroundShape.setPoint(2, sf::Vector2f(screenWidth, screenHeight));
	backgroundShape.setPoint(3, sf::Vector2f(screenWidth / 2.0f, screenHeight / 2.0f));
	backgroundShape.setPoint(4, sf::Vector2f(0.0f, screenHeight));

	// Load All Texture image files
	if (!vortexPic.loadFromFile("vortex.jpg"))
		std::cout << "Error loading vortex file" << std::endl;

	if (!applePic.loadFromFile("apple.png"))
		std::cout << "Error loading apple file" << std::endl;
	applePic.setSmooth(true);

	if (!rockPic.loadFromFile("rock.png"))
		std::cout << "Error loading rock file" << std::endl;
	rockPic.setSmooth(true);

	if (!snakeHeadPic.loadFromFile("snake-head.png"))
		std::cout << "Error loading snake file" << std::endl;

	if (!snakeBodyPic.loadFromFile("snake-body.png"))
		std::cout << "Error loading snake file" << std::endl;

	if (!grassBackground.loadFromFile("grass.jpg")) {
		std::cout << "Error loading grass file" << std::endl;
	}
	grassBackground.setRepeated(true);

	// Create the Game Window where Snake will be played
	gameWindow.setPointCount(4);
	gameWindow.setFillColor(sf::Color(200, 200, 200));
	gameWindow.setOutlineThickness(3.0f);
	gameWindow.setOutlineColor(sf::Color::White);

	gameWindow.setPoint(0, sf::Vector2f(COL(0) - 10, ROW(0) - 10));
	gameWindow.setPoint(1, sf::Vector2f(COL(X_MAX+1) - 10, ROW(0) - 10));
	gameWindow.setPoint(2, sf::Vector2f(COL(X_MAX+1) - 10, ROW(Y_MAX+1) - 10));
	gameWindow.setPoint(3, sf::Vector2f(COL(0) - 10, ROW(Y_MAX+1) - 10));
	gameWindow.setTexture(&grassBackground);

	// Load font
	if (!arial.loadFromFile(arialFile))
		std::cout << "Error loading font" << std::endl;


	gameOverWriter.setFont(arial);
	gameOverWriter.setCharacterSize(50);
	gameOverWriter.setString("GAME OVER");
	gameOverWriter.setFillColor(sf::Color::Transparent);
	gameOverWriter.setPosition(screenWidth / 2 - 200, screenHeight / 2 - 100);

	// Create the Start and Exit Buttons
	startButton.setSize(100, 50);
	startButton.setFillColor(sf::Color::Red);
	startButton.setPosition(COL(X_MAX / 2) - 40, ROW(Y_MAX / 2) - 40);
	startButton.setOutline(3.0f, sf::Color::White);

	startButton.setText("START", arialFile, 25);
	startButton.setTextColor(sf::Color::White);

	exitButton.setSize(100, 50);
	exitButton.setFillColor(sf::Color::Red);
	exitButton.setPosition(20, 20);
	exitButton.setOutline(3.0f, sf::Color::White);

	exitButton.setText("Exit", arialFile, 25);
	exitButton.setTextColor(sf::Color::White);
}

/*
   Function: executeEvent
		Responds to events received from the Main Loop such as Mouse Clicks and Keys Pressed.
   parameters:
	  event - SFML Event object
	  window - reference to current RenderWindow
   return:
	  Project* - returns a reference to the selected project object(can stay the same or change)
*/
Project* Snake::executeEvent(sf::Event event, sf::RenderWindow& window) {
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
		if (exitButton.getGlobalBounds().contains(mousePosF))
		{
			return new Menu(screenHeight, screenWidth);
		}
		else if (startButton.getGlobalBounds().contains(mousePosF))
		{
			newGame();
			nextLevel();
			startButton.setFillColor(sf::Color::Transparent);
			startButton.setOutlineColor(sf::Color::Transparent);
			startButton.setTextColor(sf::Color::Transparent);

			gameOverWriter.setFillColor(sf::Color::Transparent);
		}
	}

	// Respond to Keyboard input
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Up:
			turnUp();
			break;
		case sf::Keyboard::Down:
			turnDown();
			break;
		case sf::Keyboard::Left:
			turnLeft();
			break;
		case sf::Keyboard::Right:
			turnRight();
			break;
		}
	}

	moveSnake();
	
	return this;
}

/*
   Function: draw
		Overridden method from sf::Drawable allowing the Snake Window to be drawn normally.
   parameters:
	  event - SFML Event object
	  window - reference to current RenderWindow
*/
void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(backgroundShape);
	target.draw(gameWindow);
	target.draw(exitButton);

	// Draw the Snake
	int i = 0;
	for (i = tail; i != head; i++)
	{
		if (i == MAX_SNAKE) i = 0;
		if (i == head) break;
		sf::RectangleShape snakeSegment(sf::Vector2f(20, 20));
		snakeSegment.setOrigin(snakeSegment.getLocalBounds().width / 2.0f, snakeSegment.getLocalBounds().height / 2.0f);
		snakeSegment.setPosition(COL(snake[i].point.x), ROW(snake[i].point.y));
		snakeSegment.setTexture(&snakeBodyPic);
		target.draw(snakeSegment);
	}

	sf::RectangleShape snakeHead(sf::Vector2f(40, 40));
	snakeHead.setOrigin(snakeHead.getLocalBounds().width / 2.0f, snakeHead.getLocalBounds().height / 2.0f);
	snakeHead.setPosition(COL(snake[head].point.x), ROW(snake[head].point.y));
	snakeHead.setTexture(&snakeHeadPic);
	target.draw(snakeHead);

	// Draw each Food item
	for (i = 0; i < MAX_FOOD; i++)
	{
		if (food[i] != NULL) {
			sf::CircleShape foodDrawing(OBJECT_SIZE);
			foodDrawing.setOrigin(foodDrawing.getLocalBounds().width / 2.0f, foodDrawing.getLocalBounds().height / 2.0f);
			foodDrawing.setPosition(COL(food[i]->collectable_loc.point.x), ROW(food[i]->collectable_loc.point.y));
			foodDrawing.setTexture(&applePic);
			target.draw(foodDrawing);
		}
	}

	// Draw each Rock item
	for (i = 0; i < MAX_ROCK; i++)
	{
		if (rocks[i] != NULL) {
			sf::CircleShape rock(OBJECT_SIZE);
			rock.setOrigin(rock.getLocalBounds().width / 2.0f, rock.getLocalBounds().height / 2.0f);
			rock.setPosition(COL(rocks[i]->collectable_loc.point.x), ROW(rocks[i]->collectable_loc.point.y));
			rock.setTexture(&rockPic);
			target.draw(rock);
		}
	}

	// Draw the Wormhole item
	if (wormhole != NULL) {
		sf::CircleShape worm(OBJECT_SIZE);
		worm.setOrigin(worm.getLocalBounds().width / 2.0f, worm.getLocalBounds().height / 2.0f);
		worm.setPosition(COL(wormhole->collectable_loc.point.x), ROW(wormhole->collectable_loc.point.y));
		worm.setTexture(&vortexPic);
		target.draw(worm);
	}

	// Writes out the current Level
	sf::Text levelWriter;
	levelWriter.setFont(arial);
	levelWriter.setCharacterSize(24);
	levelWriter.setFillColor(sf::Color::Black);
	levelWriter.setPosition(screenWidth - 150, 40);
	levelWriter.setString("Level: " + std::to_string(level));
	target.draw(levelWriter);

	// Writes out the current score
	sf::Text scoreWriter;
	scoreWriter.setFont(arial);
	scoreWriter.setCharacterSize(24);
	scoreWriter.setFillColor(sf::Color::Black);
	scoreWriter.setPosition(screenWidth - 150, 100);
	std::string scoreText = score == 0 ? "Score: " + std::to_string(score) : "Score: " + std::to_string(score - 3);
	scoreWriter.setString(scoreText);
	target.draw(scoreWriter);

	target.draw(gameOverWriter);
	target.draw(startButton);
}


/*
   Function: newGame
		Initializes a new Snake game. Resets all variables and clears previous data.
*/
void Snake::newGame() {
	level = 0;
	head = 0;
	tail = 0;
	score = START_SCORE;
	eaten = 0;
	snake[head].point.x = 0;
	snake[head].point.y = 0;
	direction = RIGHT;
	game_mode = SETUP;
	int i;
	for (i = 0; i < MAX_FOOD; i++)
	{
		if (food[i] != NULL) {
			free(food[i]);
			food[i] = NULL;
		}
		if (i < 5 && rocks[i] != NULL) {
			free(rocks[i]);
			rocks[i] = NULL;
		}
	}
	if (wormhole != NULL) {
		free(wormhole);
		wormhole = NULL;
	}
}


/*
   Function: startLevel
		Transitions to the next Level. Deallocates memory and resets the eaten variable.
*/
void Snake::nextLevel()
{
	game_mode = NEXT;
	eaten = 0;
	int i;
	for (i = 0; i < MAX_FOOD; i++)
	{
		if (food[i] != NULL) {
			free(food[i]);
			food[i] = NULL;
		}
		if (i < 5 && rocks[i] != NULL) {
			free(rocks[i]);
			rocks[i] = NULL;
		}
	}
	if (wormhole != NULL) {
		free(wormhole);
		wormhole = NULL;
	}
	level++;
	startLevel();

}

/*
   Function: startLevel
		Starts the next Level in the Snake game. Sets variables to level values and ensures no collectables overlap.
*/
void Snake::startLevel() 
{
	if (level == 1) {
		// build snake
		int j = 0;
		for (j = score - 1; j > 0; --j)
		{
			addHead(&head, &direction);
		}
	}

	int numFoods;
	int value;
	if (level == 1) {
		numFoods = LEVEL_1_FOOD;
		value = 1;
	}
	else if (level == 2) {
		numFoods = LEVEL_2_FOOD;
		value = 2;
	}
	else if (level == 3) {
		numFoods = LEVEL_3_FOOD;
		value = 3;
	}
	else {
		numFoods = LEVEL_4_FOOD;
		value = 4;
	}
	int i;
	for (i = 0; i < numFoods; i++)
	{
		POINT p;
		do
		{
			p.x = rand() % X_MAX;
			p.y = rand() % Y_MAX;
		} while (isFood(p) != -1 || isSnake(p) || isRock(p));
		food[i] = newItem(p.x, p.y, value, 2);
	}
	if (level != 1) {
		int k;
		for (k = 0; k < 5; k++)
		{
			POINT p;
			do
			{
				p.x = rand() % X_MAX;
				p.y = rand() % Y_MAX;
			} while (isFood(p) != -1 || isSnake(p) || isRock(p));
			rocks[k] = newItem(p.x, p.y, value, 2);
		}
	}

	POINT p;
	do
	{
		p.x = rand() % X_MAX;
		p.y = rand() % Y_MAX;
	} while (isFood(p) != -1 || isSnake(p) || isRock(p));
	wormhole = newItem(p.x, p.y, value, 2);

	eaten = 0;
	game_mode = PLAY;
}

/*
   Function: endGame
		Ends the Game and shows the Game Over text and the restart button.
*/
void Snake::endGame()
{
	startButton.setFillColor(sf::Color::Red);
	startButton.setOutlineColor(sf::Color::White);
	startButton.setTextColor(sf::Color::White);
	game_mode = IDLE;

	std::cout << "Final Score: " << score - 3 << std::endl;
	gameOverWriter.setFillColor(sf::Color::White);

}

/*
   Function: COL
		Takes in the column number and returns the adjusted x-coordinate.
   parameters:
	  x - column number
   return:
	  int - adjusted x-coordinate
*/
int Snake::COL(int x) const {
	return x * 20 + start_x;
}

/*
   Function: ROW
		Takes in the row number and returns the adjusted y-coordinate.
   parameters:
	  y - row number
   return:
	  int - adjusted y-coordinate
*/
int Snake::ROW(int y) const {
	return y * 20 + start_y;
}

/*
   Function: newItem
		Creates a Collectable object at the given position and returns a pointer to it.
   parameters:
	  x - int x-coordinate
	  y - int y-coordinate
	  value - int item value
	  size - int size of item(length in pixels)
   return:
	  COLLECTABLE* - a pointer to the newly created Item
*/
COLLECTABLE* Snake::newItem(int x, int y, int value, int size)
{
	COLLECTABLE* item = (COLLECTABLE*)malloc(sizeof(COLLECTABLE));
	item->collectable_loc.point.x = x;
	item->collectable_loc.point.y = y;
	item->value = value;
	item->size = size;
	return item;
}

/*
   Function: isFood
		Scans the Food array to see if the selected Cell contains a Food.
   parameters:
	  p - POINT object with x and y being the column and row
   return:
	  int - the food item's index if true, -1 otherwise
*/
int Snake::isFood(POINT p)
{
	int i;
	for (i = 0; i < MAX_FOOD; i++)
	{
		if (food[i] != NULL && p.x == food[i]->collectable_loc.point.x && p.y == food[i]->collectable_loc.point.y) {
			return i;
		}
	}
	return -1;
}

/*
   Function: isRock
		Scans the Rock array to see if the selected Cell contains a Rock.
   parameters:
	  p - POINT object with x and y being the column and row
   return:
	  int - the rock item's index if true, -1 otherwise
*/
int Snake::isRock(POINT p)
{
	int i;
	for (i = 0; i < MAX_ROCK; i++)
	{
		if (rocks[i] != NULL) {
			if (p.x == rocks[i]->collectable_loc.point.x && p.y == rocks[i]->collectable_loc.point.y) {
				return 1;
			}
		}
	}
	return 0;
}


/*
   Function: isWorm
		Checks to see if the selected Cell contains the Wormhole.
   parameters:
	  p - POINT object with x and y being the column and row
   return:
	  int - 1 if true, 0 otherwise
*/
int Snake::isWorm(POINT p)
{
	if (wormhole != NULL) {
		if (p.x == wormhole->collectable_loc.point.x && p.y == wormhole->collectable_loc.point.y)
		{
			return 1;
		}
	}
	return 0;
}

/*
   Function: isSnake
		Scans the Snake Body array to see if the selected Cell contains a a segment of the snake.
   parameters:
	  p - POINT object with x and y being the column and row
   return:
	  int - 1 if true, 0 otherwise
*/
int Snake::isSnake(POINT p)
{
	int i;
	for (i = tail; i != head; i++)
	{
		if (i == MAX_SNAKE) i = 0;
		if (i == head) break;
		if (p.x == snake[i].point.x && p.y == snake[i].point.y) {
			return 1;
		}
	}
	return 0;
}

/*
   Function: addHead
		Moves the snake's head to its next Location according to the direction. 
		Checks wall collision to prevent the snake from escaping and to apply the different level rulesets
	parameters:
		*head - pointer to the current head index
		*direction - pointer to the current direction enum value
*/
void Snake::addHead(int* head, int* direction)
{
	// increment head index (handle wrap around using bitwise operator)
	int new_head = (*head + 1) & (~MAX_SNAKE);
	snake[new_head] = snake[*head];		// set new head to previous head
	*head = new_head;

	// iterate until valid move (new head)
	while (1)
	{
		switch (*direction)
		{
		case RIGHT:
			// if room to the right, then move right
			if (snake[new_head].point.x < X_MAX)	// room to move right?
			{
				snake[new_head].point.x++;		// y, move right
			}
			else
			{										// else at right fence
				switch (level)
				{
				case 1:							// level 1: wrap around
					snake[new_head].point.x = 0;
					break;

				case 2:							// level 2: 90 degrees
					*direction = snake[new_head].point.y < Y_MAX/2
						? DOWN : UP;
					continue;					// try again

				case 3:							// level 3: death by electrocution!
				case 4:							// level 4: death by electrocution!
				default:
					endGame();
				}
			}
			break;									// new head

		case UP:
			// if room up, then move up
			if (snake[new_head].point.y > 0)
			{
				--(snake[new_head].point.y);		// move up
			}
			else
			{										// else at top fence
				switch (level)
				{
				case 1:							// level 1: wrap around
					snake[new_head].point.y = Y_MAX;
					break;

				case 2:							// level 2: 90 degrees
					*direction = snake[new_head].point.x > X_MAX/2
						? LEFT : RIGHT;
					continue;					// try again

				case 3:							// level 3: death by electrocution!
				case 4:							// level 4: death by electrocution!
				default:
					endGame();
				}
			}
			break;									// new head

		case LEFT:
			// if room left, then move left
			if (snake[new_head].point.x > 0)
			{
				--(snake[new_head].point.x);		// move left
			}
			else
			{										// else at left fence
				switch (level)
				{
				case 1:							// level 1: wrap around
					snake[new_head].point.x = X_MAX;
					break;

				case 2:							// level 2: 90 degrees
					*direction = snake[new_head].point.y < Y_MAX/2
						? DOWN : UP;
					continue;					// try again

				case 3:							// level 3: death by electrocution!
				case 4:							// level 4: death by electrocution!
				default:
					endGame();
				}
			}
			break;									// new head

		case DOWN:
			// if room down, then move down
			if (snake[new_head].point.y < Y_MAX)
			{
				++(snake[new_head].point.y);		// move down
			}
			else
			{										// else at bottom fence
				switch (level)
				{
				case 1:							// level 1: wrap around
					snake[new_head].point.y = 0;
					break;

				case 2:							// level 2: 90 degrees
					*direction = snake[new_head].point.x > X_MAX/2
						? LEFT : RIGHT;
					continue;					// try again

				case 3:							// level 3: death by electrocution!
				case 4:							// level 4: death by electrocution!
				default:
					endGame();
				}
			}
			break;									// new head

		} // end switch
		break;											// done, draw head
	} // end while
}

/*
   Function: moveSnake
		Moves the head using the addHead function, then checks for collectables in that cell and will either end the game or adjust the head and delete the tail.
	parameters:
		*head - pointer to the current head index
		*direction - pointer to the current direction enum value
*/
void Snake::moveSnake()
{
	if (level > 0 && game_mode != IDLE)
	{
		addHead(&head, &direction);		// add head

		POINT h;
		h.x = snake[head].point.x;
		h.y = snake[head].point.y;
		if (isFood(h) != -1) {
			std::cout << "Hit food!" << std::endl;
			int pos;
			pos = isFood(h);
			if (food[pos] != NULL) {
				score += level;
				eaten++;

				if (level != 2) {
					POINT p;
					do
					{
						p.x = rand() % X_MAX;
						p.y = rand() % Y_MAX;
					} while (isFood(p) != -1 || isSnake(p) || isRock(p));
					free(food[pos]);
					food[pos] = newItem(p.x, p.y, 1, 2);
				}
				else {
					free(food[pos]);
					food[pos] = NULL;
				}
			}
			else {
				tail = (tail + 1) & (~MAX_SNAKE);
			}
		}
		else if (isWorm(h)) {
			std::cout << "Hit wormhole!" << std::endl;
			tail = (tail + 1) & (~MAX_SNAKE);
			POINT p;
			do
			{
				p.x = rand() % X_MAX;
				p.y = rand() % Y_MAX;
			} while (isFood(p) != -1 || isSnake(p) || isRock(p));
			int new_head = (head + 1) & (~MAX_SNAKE);
			snake[new_head] = snake[head];     // set new head to previous head
			head = new_head;
			snake[head].point.x = p.x;
			snake[head].point.y = p.y;

			free(wormhole);
			wormhole = NULL;

			tail = (tail + 1) & (~MAX_SNAKE); // delete tail
		}
		
		else if (isSnake(h)) {
			std::cout << "Hit itself!" << std::endl;
			endGame();

		}
		else if (isRock(h)) {
			std::cout << "Hit rock!" << std::endl;
			endGame();

		}
		else {
			tail = (tail + 1) & (~MAX_SNAKE); // delete tail
		}
		if (eaten == 10) {
			nextLevel();
		}
	}
}

/*
   Function: turnLeft
		Switches the direction to LEFT if you are able to.
*/
void Snake::turnRight()
{
	switch (direction)
	{
	case UP:
		if ((level == 1) || (snake[head].point.x <= X_MAX))
		{
			direction = RIGHT;
		}
		break;
	case DOWN:
		if ((level == 1) || (snake[head].point.x <= X_MAX))
		{
			direction = RIGHT;
		}
		break;
	case RIGHT:					// ignore if going right
	case LEFT:					// ignore if going left
		break;
	}
}

/*
   Function: turnLeft
		Switches the direction to LEFT if you are able to.
*/
void Snake::turnLeft()
{
	switch (direction)
	{
	case UP:
		if ((level == 1) || (snake[head].point.x >= 0))
		{
			direction = LEFT;
		}
		break;
	case DOWN:
		if ((level == 1) || (snake[head].point.x >= 0))
		{
			direction = LEFT;
		}
		break;
	case RIGHT:                 // ignore if going right
	case LEFT:                  // ignore if going left
		break;
	}
}

/*
   Function: turnUp
		Switches the direction to UP if you are able to.
*/
void Snake::turnUp()
{
	switch (direction)
	{
	case RIGHT:
		if ((level == 1) || (snake[head].point.y <= Y_MAX))
		{
			direction = UP;
		}
		break;
	case LEFT:
		if ((level == 1) || (snake[head].point.y <= Y_MAX))
		{
			direction = UP;
		}
		break;
	case UP:                 // ignore if going right
	case DOWN:                  // ignore if going left
		break;
	}
}

/*
   Function: turnDown
		Switches the direction to DOWN if you are able to.
*/
void Snake::turnDown()
{
	switch (direction)
	{
	case RIGHT:
		if ((level == 1) || (snake[head].point.y >= 0))
		{
			direction = DOWN;
		}
		break;
	case LEFT:
		if ((level == 1) || (snake[head].point.y >= 0))
		{
			direction = DOWN;
		}
		break;
	case UP:                 // ignore if going right
	case DOWN:                  // ignore if going left
		break;
	}
}