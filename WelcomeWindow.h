#include <SFML/Graphics.hpp>

class WelcomeWindow {
private:
    sf::Font font;
    float width;
    float height;
    std::string name;
    sf::RenderWindow leaderboard;

public:
    WelcomeWindow(sf::Font font, int width, int height) {
        this->font = font;
        this->width = width;
        this->height = height;
    }

    void setText(sf::Text &text, float x, float y);
    std::string displayWindow(bool& runGame);
};


