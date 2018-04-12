#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 800;
const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;
const int GRID_WIDTH_SIZE = WIDTH / GRID_WIDTH;
const int GRID_HEIGHT_SIZE = WIDTH / GRID_HEIGHT;
int grid[GRID_WIDTH][GRID_HEIGHT] = { 0 };

int main(int argc, char *argv[]) {
  int score = 1;
  sf::Text scoreText;
  sf::Font font;
  font.loadFromFile("LemonMilk.otf");
  scoreText.setColor(sf::Color::Red);
  scoreText.setPosition(WIDTH + 100, HEIGHT / 2);
  scoreText.setFont(font);
  scoreText.setCharacterSize(128);
  int xFoodPos, yFoodPos;
  int moveSnake[2] = {1, 0};
  std::vector<std::pair<int, int>> tail;
  tail.push_back(std::make_pair(GRID_WIDTH / 2, GRID_HEIGHT / 2));
  grid[tail.at(0).first][tail.at(0).second] = 1;
  srand(time(NULL));
  do {
    xFoodPos = rand() % 10;
    yFoodPos = rand() % 10;
  } while (grid[xFoodPos][yFoodPos] != 0);
  grid[xFoodPos][yFoodPos] = 2;
  sf::RectangleShape food;
  sf::RectangleShape snakePart;
  food.setSize(sf::Vector2f(GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE));
  food.setFillColor(sf::Color::Red);
  food.setOutlineThickness(0);
  food.setPosition(xFoodPos * GRID_WIDTH_SIZE, yFoodPos * GRID_HEIGHT_SIZE);
  snakePart.setSize(sf::Vector2f(GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE));
  snakePart.setOutlineThickness(0);
  snakePart.setFillColor(sf::Color::Green);

  sf::RenderWindow window(sf::VideoMode(WIDTH + 400, HEIGHT), "Snake Game!");
  window.setFramerateLimit(10);

  sf::RectangleShape backgroundBoard;
  backgroundBoard.setSize(sf::Vector2f(GRID_WIDTH * GRID_WIDTH_SIZE, GRID_HEIGHT * GRID_HEIGHT_SIZE));
  backgroundBoard.setPosition(0, 0);
  backgroundBoard.setFillColor(sf::Color::White);

  bool foodCollected = false;

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right) {
          moveSnake[0] = 1;
          moveSnake[1] = 0;
        }
        if (event.key.code == sf::Keyboard::Left) {
          moveSnake[0] = -1;
          moveSnake[1] = 0;
        }
        if (event.key.code == sf::Keyboard::Up) {
          moveSnake[0] = 0;
          moveSnake[1] = -1;
        }
        if (event.key.code == sf::Keyboard::Down) {
          moveSnake[0] = 0;
          moveSnake[1] = 1;
        }
      }
    }

    int currentX = tail.at(tail.size() - 1).first;
    int currentY = tail.at(tail.size() - 1).second;

    currentX += moveSnake[0];
    currentY += moveSnake[1];

    if (grid[currentX][currentY] == 2 && currentX == xFoodPos && currentY == yFoodPos) {
      foodCollected = true;
      tail.push_back(std::make_pair(xFoodPos, yFoodPos));
      score++;
      grid[xFoodPos][yFoodPos] = 1;
    } else if (grid[currentX][currentY] == 1) {
      std::cout << "Game Over - You ate yourself\n";
    } else if (currentX < 0 || currentX >= GRID_WIDTH || currentY < 0 || currentY >= GRID_HEIGHT) {
      std::cout << "Game Over - Out of board\n";
    } else {
      tail.push_back(std::make_pair(currentX, currentY));
      grid[tail.at(tail.size() - 1).first][tail.at(tail.size() - 1).second] = 1;
      grid[tail.at(0).first][tail.at(0).second] = 0;
      tail.erase(tail.begin(), tail.begin() + 1);
    }

    std::stringstream ss;
    ss << score;
    scoreText.setString(ss.str().c_str());

    window.clear();  
    window.draw(backgroundBoard);
   
    for (int i = tail.size() - 1; i >= 0; i--) {
      snakePart.setPosition(tail.at(i).first * GRID_WIDTH_SIZE, tail.at(i).second * GRID_HEIGHT_SIZE);
      window.draw(snakePart);
    }

    if (!foodCollected) {
      window.draw(food);
    }
    window.draw(scoreText);
    std::cout << score << "\n";
    window.display();

    if (foodCollected == true) {
      do {
        xFoodPos = rand() % 10;
        yFoodPos = rand() % 10;
      } while (grid[xFoodPos][yFoodPos] != 0);
      food.setPosition(xFoodPos * GRID_WIDTH_SIZE, yFoodPos * GRID_HEIGHT_SIZE);
      grid[xFoodPos][yFoodPos] = 2;
      foodCollected = false;
    }
  }  
  return 0;
}
