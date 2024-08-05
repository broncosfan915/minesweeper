class Cell {
public:
    bool hasBomb = false;
    bool isRevealed = false;
    bool hasFlag = false;
    std::vector<Cell*> surroundingCells;
    int xPosition;
    int yPosition;
    int numBombs;

    //in order to get resize to work;
    Cell() {
        bool hasBomb = false;
        bool isRevealed = false;
        bool hasFlag = false;
        int xPosition = 0;
        int yPosition = 0;
    }

    Cell(int xPosition, int yPosition) {
        this->xPosition = xPosition;
        this->yPosition = yPosition;

    }
};
