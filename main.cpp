#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

void setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

int main() {
    // reading the config file
    std::string configPath = "files/config.cfg";
    std::ifstream file;
    file.open(configPath);

    // loading the font
    sf::Font font;
    font.loadFromFile("files/font.ttf");

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

    int width = colCount * 32;
    int height = (colCount * 32) + 100;

    sf::RenderWindow welcomeWindow(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);

    sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
    setText(welcomeText, width/2, (height/2) - 150);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::Text enterNameText("Enter your name:", font, 20);
    setText(enterNameText, width/2, height/2 - 75);
    enterNameText.setFillColor((sf::Color::White));
    enterNameText.setStyle(sf::Text::Bold);

    std::string name;
    while(welcomeWindow.isOpen()) {
        sf::Event event;
        while(welcomeWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
            welcomeWindow.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 13 && name.length() > 0) {
                    welcomeWindow.close();
                }
                if (event.text.unicode == '\b' && name.length() > 0) {
                    name.pop_back();
                    continue;
                }
                else if (std::isalpha(static_cast<char>(event.text.unicode))) {
                    if (name.length() != 10) {
                        if (name.length() == 0) {
                            name += std::toupper(static_cast<char>(event.text.unicode));
                        }
                        else {
                            name += std::tolower(static_cast<char>(event.text.unicode));
                        }
                    }
                }
            }
        }
        sf::Text nameText(name + "|", font, 18);
        setText(nameText, width/2, height/2 - 45);
        nameText.setFillColor(sf::Color::Yellow);

    welcomeWindow.clear(sf::Color::Blue);
    welcomeWindow.draw(welcomeText);
    welcomeWindow.draw(enterNameText);
    welcomeWindow.draw(nameText);
    welcomeWindow.display();
    }
    return 0;
}