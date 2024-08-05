#include <iostream>
#include <fstream>
#include "WelcomeWindow.h"
#include "Board.h"
#include <SFML/Graphics.hpp>


int main() {
    // reading the config file
    std::string configPath = "./files/config.cfg";
    std::ifstream file;
    file.open(configPath);

    // loading the font
    sf::Font font;
    font.loadFromFile("./files/font.ttf");

    // setting the num of rows columns and bombs
    std::string colCountString;
    std::getline(file, colCountString);
    int colCount = stoi(colCountString);

    std::string rowCountString;
    std::getline(file, rowCountString);
    int rowCount = stoi(rowCountString);

    std::string bombCountString;
    std::getline(file, bombCountString);
    int bombCount = stoi(bombCountString);

    float width = float(colCount) * 32;
    float height = float(rowCount * 32) + 100;
    bool runGame = false;

    WelcomeWindow window(font, width, height);
    std::string name = window.displayWindow(runGame);

    if (runGame) {
        Board board(width, height, colCount, rowCount, bombCount, font);
        board.displayBoard(name);
    }


    return 0;
}