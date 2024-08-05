#include <string>
#include <utility>
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Leaderboard {
private:
    int height;
    int width;
    int total_time;
    int minutes;
    int seconds;
    bool gameWon;
    bool leaderboardDisplayed;
    std::string name;
    std::vector<std::string> times;
    std::vector<std::string> names;
    sf::RenderWindow leaderboard;
    std::string leaderboardString;
    sf::Font font;


public:
    Leaderboard(int rowCount, int colCount, std::string name, int total_time, int minutes, int seconds, sf::Font font, bool gameWon, bool &leaderboardDisplayed) {
        height = (rowCount * 16) + 50;
        width = (colCount * 16);

        this->total_time = total_time;
        this->font = font;
        this->gameWon = gameWon;
        this->leaderboardDisplayed = leaderboardDisplayed;
        this->name = name;
        this->minutes = minutes;
        this->seconds = seconds;
    }

    bool isClosed() {
        return !leaderboard.isOpen();
    }

    bool isOpen() {
        return leaderboard.isOpen();
    }

    void displayLeaderboard();
    void setText(sf::Text &text, float x, float y);
    int findSmaller();
    };
