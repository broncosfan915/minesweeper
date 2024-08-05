#include "Leaderboard.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void Leaderboard::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void Leaderboard::displayLeaderboard() {
    std::cout << name << std::endl;
    leaderboard.create(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
    std::ifstream file("./files/leaderboard.txt");

    sf::Text leaderboardText("LEADERBOARD", font, 24);
    setText(leaderboardText, width / 2, (height / 2) - 120);
    leaderboardText.setFillColor(sf::Color::White);
    leaderboardText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    std::string line;
    for (int i = 0; i < 5; i ++) {
        getline(file,line);
        std::stringstream ss(line);

        std::string time;
        getline(ss, time, ',');
        times.push_back(time);

        std::string prevName;
        getline(ss, prevName, ',');
        prevName.erase(0, 1);
        names.push_back(prevName);
    }


    int newIndex = findSmaller();

    int minutes0 = minutes / 10 % 10;
    int minutes1 = minutes % 10;
    int seconds0 = seconds / 10 % 10;
    int seconds1 = seconds % 10;

    std::string userTime =  std::to_string(minutes0) + std::to_string(minutes1) + ":" + std::to_string(seconds0) + std::to_string(seconds1);
    std::cout << userTime << name << std::endl;

    if (newIndex != 10) {
        names.insert(names.begin() + newIndex, name);
        names.pop_back();

        times.insert(times.begin() + newIndex, userTime);
        times.pop_back();
    }

    for (int i = 0; i < 5; i++) {
        std::string strPlace = std::to_string(i + 1);

        if (i == newIndex) {
            leaderboardString += strPlace + ".\t" + times[i] + "\t" + names[i] + "*" + "\n\n";
        }
        else {
            leaderboardString += strPlace + ".\t" + times[i] + "\t" + names[i] + "\n\n";
        }
    }
    file.close();

    std::ofstream outfile ("./files/leaderboard.txt", std::ios::out | std::ios::trunc);
    for (int i = 0; i < 5; i++) {
        outfile << times[i] << ", " << names[i] << std::endl;
    }
    outfile.close();

    while (leaderboard.isOpen()) {
        sf::Event event;
        if (leaderboardDisplayed) {
        }
        while (leaderboard.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderboardDisplayed = false;
                leaderboard.close();
                return;
            }
        }

        sf::Text leaderboardContent(leaderboardString, font, 18);
        setText(leaderboardContent, width / 2, (height / 2) + 20);
        leaderboardContent.setFillColor(sf::Color::White);
        leaderboardContent.setStyle(sf::Text::Bold);

        leaderboard.clear(sf::Color::Blue);
        leaderboard.draw(leaderboardText);
        leaderboard.draw(leaderboardContent);
        leaderboard.display();
    }
}

int Leaderboard::findSmaller() {
    int tempTime;

    if (gameWon) {
        for (int i = 0; i < 5; i++) {
            int minutes = stoi(times[i].substr(0, 2));
            int seconds = stoi(times[i].substr(3, 2));
            int tempTime = minutes * 60 + seconds;

            if (total_time < tempTime) {
                return i;
            }
        }
    }
    return 10;
}