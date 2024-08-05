#include <SFML/Graphics.hpp>
#include <chrono>
#include "Cell.h"
#include "Leaderboard.h"

class Board {
private:
    float width;
    float height;
    int colCount;
    int rowCount;
    int bombCount;
    int total_time;
    int counterNum;
    int minutes;
    int seconds;
    bool generatedRandom = false;
    bool debugClicked = false;
    bool gameLost = false;
    bool gameWon = false;
    bool gamePaused = false;
    bool leaderboardDisplayed;

//
//    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
//    std::chrono::time_point<std::chrono::high_resolution_clock> elapsed_pause_time;
//    std::chrono::time_point<std::chrono::high_resolution_clock> pauseTime;



    sf::Sprite happyFace;
    sf::Sprite pauseButton;
    sf::Sprite playButton;
    sf::Sprite loseFace;
    sf::Sprite winFace;
    sf::Sprite currFace;
    sf::Sprite currPausePlay;
    sf::Sprite numberOne;
    sf::Sprite numberTwo;
    sf::Sprite numberThree;
    sf::Sprite numberFour;
    sf::Sprite numberFive;
    sf::Sprite numberSix;
    sf::Sprite numberSeven;
    sf::Sprite numberEight;

    sf::RenderWindow board;

    sf::Font font;

    std::vector<Cell> cells;
    // for reverting to the previous board from pause
    std::vector<Cell> prevCells;

public:
    Board(float width, float height, int colCount, int rowCount, int bombCount, sf::Font font) {
        this->width = width;
        this->height = height;
        this->colCount = colCount;
        this->rowCount = rowCount;
        this->bombCount = bombCount;
        this->counterNum = bombCount;

        this->font = font;
    }

    void displayBoard(std::string name);
    void placeFlag(int xValue, int yValue);
    void placeRevealedTile(int xValue, int yValue);
    void resetBoard();
    void generateBombs();
    void allRevealed();
    void previousState();
    void findAdjacentCells(int index);
    void findBombs(int index);
    void displayEmptyCells(int index);
    void checkIfWinner();

    // for the timer
    std::map<int, sf::Sprite> parseDigits(sf::Sprite digits);

};
