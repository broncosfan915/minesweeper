#include "WelcomeWindow.h"

void WelcomeWindow::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

    std::string WelcomeWindow::displayWindow(bool& runGame) {
    sf::RenderWindow welcomeWindow(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);

    sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
    setText(welcomeText, width / 2, (height / 2) - 150);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::Text enterNameText("Enter your name:", font, 20);
    setText(enterNameText, width / 2, height / 2 - 75);
    enterNameText.setFillColor((sf::Color::White));
    enterNameText.setStyle(sf::Text::Bold);

    std::string name;
    while (welcomeWindow.isOpen()) {
        sf::Event event;

        while (welcomeWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                welcomeWindow.close();
                runGame = false;
            }

            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 13 && !name.empty()) {
                    runGame = true;
                    welcomeWindow.close();
                }
                else if (event.text.unicode == '\b' && !name.empty()) {
                    name.pop_back();
                    continue;
                }
                else if (std::isalpha(static_cast<char>(event.text.unicode))) {
                    if (name.length() != 10) {
                        if (name.empty()) {
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
        setText(nameText, width / 2, height / 2 - 45);
        nameText.setFillColor(sf::Color::Yellow);

        welcomeWindow.clear(sf::Color::Blue);
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(enterNameText);
        welcomeWindow.draw(nameText);
        welcomeWindow.display();
    }
    return name;
}
