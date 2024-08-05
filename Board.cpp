#include "Board.h"
#include "TextureManager.h"
#include<iostream>
#include<map>
#include<chrono>


void Board::displayBoard(string name) {
    board.create(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
    // setting variables and textures for the timer
    auto start_time = std::chrono::high_resolution_clock::now();

    auto pauseTime = std::chrono::high_resolution_clock::now();
    auto elapsed_pause_time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()-pauseTime).count();


    sf::Texture& digitsText = TextureManager::getTexture("digits");
    TextureManager::displayTextures();
    sf::Sprite digits;
    digits.setTexture(digitsText);

    map <int, sf::Sprite> digitsMap = parseDigits(digits);


    sf::Texture debugButtonTexture;
    debugButtonTexture.loadFromFile("./files/images/debug.png");
    sf::Sprite debugButton(debugButtonTexture);
    debugButton.setPosition((colCount * 32) - 304, 32 * (rowCount + 0.5));

    sf::Texture pauseButtonTexture;
    pauseButtonTexture.loadFromFile("./files/images/pause.png");
    pauseButton.setTexture(pauseButtonTexture);
    pauseButton.setPosition((colCount * 32) - 240, 32 * (rowCount + 0.5));

    sf::Texture playButtonTexture;
    playButtonTexture.loadFromFile("./files/images/play.png");
    playButton.setTexture(playButtonTexture);
    playButton.setPosition((colCount * 32) - 240, 32 * (rowCount + 0.5));

    sf::Texture leaderboardButtonTexture;
    leaderboardButtonTexture.loadFromFile("./files/images/leaderboard.png");
    sf::Sprite leaderboardButton(leaderboardButtonTexture);
    leaderboardButton.setPosition((colCount * 32) - 176, 32 * (rowCount + 0.5));

    sf::Texture happyFaceTexture;
    happyFaceTexture.loadFromFile("./files/images/face_happy.png");
    happyFace.setTexture(happyFaceTexture);
    happyFace.setPosition(((colCount / 2.0) * 32) - 32, 32 * (rowCount + 0.5));

    sf::Texture winFaceTexture;
    winFaceTexture.loadFromFile("./files/images/face_win.png");
    winFace.setTexture(winFaceTexture);
    winFace.setPosition(((colCount / 2.0) * 32) - 32, 32 * (rowCount + 0.5));

    sf::Texture loseFaceTexture;
    loseFaceTexture.loadFromFile("./files/images/face_lose.png");
    loseFace.setTexture(loseFaceTexture);
    loseFace.setPosition(((colCount / 2.0) * 32) - 32, 32 * (rowCount + 0.5));

    sf::Texture hiddenTileTexture;
    hiddenTileTexture.loadFromFile("./files/images/tile_hidden.png");
    sf::Sprite hiddenTile(hiddenTileTexture);

    sf::Texture revealedTileTexture;
    revealedTileTexture.loadFromFile("./files/images/tile_revealed.png");
    sf::Sprite revealedTile(revealedTileTexture);

    sf::Texture flagTexture;
    flagTexture.loadFromFile("./files/images/flag.png");
    sf::Sprite flag(flagTexture);

    sf::Texture bombTexture;
    bombTexture.loadFromFile("./files/images/mine.png");
    sf::Sprite bomb(bombTexture);

    sf::Texture numberOneTexture;
    numberOneTexture.loadFromFile("./files/images/number_1.png");
    sf::Sprite numberOne(numberOneTexture);

    sf::Texture numberTwoTexture;
    numberTwoTexture.loadFromFile("./files/images/number_2.png");
    numberTwo.setTexture(numberTwoTexture);

    sf::Texture numberThreeTexture;
    numberThreeTexture.loadFromFile("./files/images/number_3.png");
    numberThree.setTexture(numberThreeTexture);

    sf::Texture numberFourTexture;
    numberFourTexture.loadFromFile("./files/images/number_4.png");
    numberFour.setTexture(numberFourTexture);

    sf::Texture numberFiveTexture;
    numberFiveTexture.loadFromFile("./files/images/number_5.png");
    numberFive.setTexture(numberFiveTexture);

    sf::Texture numberSixTexture;
    numberSixTexture.loadFromFile("./files/images/number_6.png");
    numberSix.setTexture(numberSixTexture);

    sf::Texture numberSevenTexture;
    numberSevenTexture.loadFromFile("./files/images/number_7.png");
    numberSeven.setTexture(numberSevenTexture);

    sf::Texture numberEightTexture;
    numberEightTexture.loadFromFile("./files/images/number_8.png");
    numberEight.setTexture(numberEightTexture);

    sf::Texture digitsTexture;
    digitsTexture.loadFromFile("./files/images/digits.png");
    sf::Sprite digitsSprite(digitsTexture);

    sf::IntRect negativeRect(210, 0, 21, 32);
    digitsSprite.setTextureRect(negativeRect);

    currFace = happyFace;
    currPausePlay = pauseButton;

    while (board.isOpen()) {
        sf::Event event;
        while (board.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                board.close();
            }
             else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Mouse mouse;
                int mouseX = mouse.getPosition(board).x;
                int mouseY = mouse.getPosition(board).y;


                if (leaderboardButton.getGlobalBounds().contains(mouseX, mouseY)) {
                    pauseTime = chrono::high_resolution_clock::now();
                    Leaderboard leaderboard(rowCount, colCount, name, total_time, minutes, seconds ,font, gameWon, gamePaused);
                    leaderboard.displayLeaderboard();

                    auto unPausedTime = chrono::high_resolution_clock::now();
                    elapsed_pause_time += chrono::duration_cast<chrono::seconds>(unPausedTime - pauseTime).count();
                }

                else if ((currPausePlay.getGlobalBounds().contains(mouseX, mouseY) && !gameLost && !gameWon)) {
                    if (currPausePlay.getTexture() == pauseButton.getTexture()) {
                        allRevealed();
                        gamePaused = true;
                        currPausePlay = playButton;
                    }
                    else if (currPausePlay.getTexture() == playButton.getTexture()) {
                        previousState();
                        gamePaused = false;
                        currPausePlay = pauseButton;
                    }
                    if (gamePaused || gameLost || gameWon) {
                        pauseTime = chrono::high_resolution_clock::now();
                    }
                    else {
                        // possibly steady
                        auto unPausedTime = chrono::high_resolution_clock::now();
                        elapsed_pause_time += chrono::duration_cast<chrono::seconds>(unPausedTime - pauseTime).count();
                    }
                }

                if (debugButton.getGlobalBounds().contains(mouseX, mouseY) && !gamePaused && !gameLost && !gameWon) {
                    if (debugClicked) {
                        debugClicked = false;
                    } else if (!debugClicked) {
                        debugClicked = true;
                    }
                }
                // checking if the mouse clicked on the face button, and resetting the board if true
                else if (currFace.getGlobalBounds().contains(mouseX, mouseY)) {
                    gameLost = false;
                    gameWon = false;
                    gamePaused = false;
                    currPausePlay = pauseButton;
                    resetBoard();

                    total_time = 0;
                    pauseTime = std::chrono::high_resolution_clock::now();
                    start_time = std::chrono::high_resolution_clock::now();
                    elapsed_pause_time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()-pauseTime).count();

                    counterNum = bombCount;
                }

                //checking if the mouse click was on any of the tiles, and changing the sprite if true
                else if (!gamePaused && !gameWon && !gameLost){
                    for (int i = 0; i < rowCount; i++) {
                        for (int j = 0; j < colCount; j++) {
                            int xValue = j * 32;
                            int yValue = i * 32;

                            hiddenTile.setPosition(xValue, yValue);
                            if (hiddenTile.getGlobalBounds().contains(mouseX, mouseY)) {
                                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                                    placeFlag(xValue, yValue);
                                }
                                else {
                                    placeRevealedTile(xValue, yValue);
                                }
                            }
                        }
                    }
                }
            }
        }
        board.clear(sf::Color::White);

        //logic for the timer
        auto game_duration = std::chrono::duration_cast<std::chrono::seconds>(chrono::high_resolution_clock::now() - start_time);
        total_time = game_duration.count();


        if(!gamePaused && !gameLost && !gameWon) {
            total_time = total_time - elapsed_pause_time;
            minutes = total_time / 60;
            seconds = total_time % 60;
        }


        int minutes0 = minutes / 10 % 10;
        int minutes1 = minutes % 10;
        int seconds0 = seconds / 10 % 10;
        int seconds1 = seconds % 10;

        digitsMap[minutes0].setPosition(colCount * 32 - 97, 32 * (rowCount + 0.5f) + 16);
        board.draw(digitsMap[minutes0]);
        digitsMap[minutes1].setPosition(colCount * 32 - 76, 32 * (rowCount + 0.5f) + 16);
        board.draw(digitsMap[minutes1]);
        digitsMap[seconds0].setPosition(colCount * 32 - 54, 32 * (rowCount + 0.5f) + 16);
        board.draw(digitsMap[seconds0]);
        digitsMap[seconds1].setPosition(colCount * 32 - 33, 32 * (rowCount + 0.5f) + 16);
        board.draw(digitsMap[seconds1]);

        int digits0 = abs(counterNum % 10);
        int digits1 = abs(counterNum / 10 % 10);
        int digits2 = abs(counterNum / 100 % 10);


        digitsMap[digits0].setPosition(33 + 21 + 21, 32 * (rowCount + 0.5f) + 16);
        board.draw(digitsMap[digits0]);
        digitsMap[digits1].setPosition(33 + 21, 32 * (rowCount + 0.5f) + 16);
        board.draw(digitsMap[digits1]);

        if (counterNum < 0) {
            digitsSprite.setPosition(33 -21, 32 * (rowCount + 0.5f) + 16);
            board.draw(digitsSprite);

            digitsMap[digits2].setPosition(33, 32 * (rowCount + 0.5f) + 16);
            board.draw(digitsMap[digits2]);
        }
        else {
            digitsMap[digits2].setPosition(33, 32 * (rowCount + 0.5f) + 16);
            board.draw(digitsMap[digits2]);
        }

        //adding the amount of tiles to the vector
        if (cells.empty()) {
            for (int i = 0; i < rowCount; i++) {
                for (int j = 0; j < colCount; j++) {
                    int xValue = j * 32;
                    int yValue = i * 32;

                    cells.emplace_back(xValue, yValue);
                }
            }
        }

        //finding the adjacent tiles for every cell in the vector
        for (int i = 0; i < cells.size(); i++) {
            findAdjacentCells(i);
        }

        //generating random places for the bombs
            generateBombs();

        for (int i = 0; i < cells.size(); i++) {
            findBombs(i);
        }

        // checking if the user has won
        checkIfWinner();
        if (gameWon) {
            counterNum = 0;
            Leaderboard leaderboard(rowCount, colCount, name, total_time, minutes, seconds ,font, gameWon, gamePaused);

            currFace = winFace;

            for (int i = 0; i < cells.size(); i++) {
                if (cells[i].hasBomb) {
                    cells[i].hasFlag = true;
                }
            }
        }

        //drawing the tiles on the board
        for (int i = 0; i < cells.size(); i++) {
            if (!cells[i].isRevealed) {
                hiddenTile.setPosition(cells[i].xPosition, cells[i].yPosition);
                board.draw(hiddenTile);

                if (cells[i].hasFlag) {
                    flag.setPosition(cells[i].xPosition, cells[i].yPosition);
                    board.draw(flag);
                }

                if (!gameWon) {
                    if ((debugClicked || gameLost) && cells[i].hasBomb) {
                        bomb.setPosition(cells[i].xPosition, cells[i].yPosition);
                        board.draw(bomb);
                    }
                }
            }
            else {
                if (cells[i].hasFlag && cells[i].isRevealed) {
                    cells[i].isRevealed = false;
                }

                revealedTile.setPosition(cells[i].xPosition, cells[i].yPosition);
                if (!cells[i].hasFlag) {
                    displayEmptyCells(i);
                }
                board.draw(revealedTile);


                if (cells[i].hasBomb && !cells[i].hasFlag) {
                    currFace = loseFace;
                    gameLost = true;

                    pauseTime = chrono::high_resolution_clock::now();

                    bomb.setPosition(cells[i].xPosition, cells[i].yPosition);
                    board.draw(bomb);
                }

                    if (cells[i].numBombs == 1) {
                        numberOne.setPosition(cells[i].xPosition, cells[i].yPosition);
                        board.draw(numberOne);
                    } else if (cells[i].numBombs == 2) {
                        numberTwo.setPosition(cells[i].xPosition, cells[i].yPosition);
                        board.draw(numberTwo);
                    } else if (cells[i].numBombs == 3) {
                        numberThree.setPosition(cells[i].xPosition, cells[i].yPosition);
                        board.draw(numberThree);
                    } else if (cells[i].numBombs == 4) {
                        numberFour.setPosition(cells[i].xPosition, cells[i].yPosition);
                        board.draw(numberFour);
                    } else if (cells[i].numBombs == 5) {
                        numberFive.setPosition(cells[i].xPosition, cells[i].yPosition);
                        board.draw(numberFive);
                    } else if (cells[i].numBombs == 6) {
                        numberSix.setPosition(cells[i].xPosition, cells[i].yPosition);
                        board.draw(numberSix);
                    } else if (cells[i].numBombs == 7) {
                        numberSeven.setPosition(cells[i].xPosition, cells[i].yPosition);
                        board.draw(numberSeven);
                    } else if (cells[i].numBombs == 8) {
                        numberEight.setPosition(cells[i].xPosition, cells[i].yPosition);
                        board.draw(numberEight);
                    }

            }
        }

        board.draw(currFace);
        board.draw(debugButton);
        board.draw(currPausePlay);
        board.draw(leaderboardButton);
        board.display();
    }
}

// looks through the vector of cells to see which one the user clicked on, and changing the flag variable to true
void Board::placeFlag(int xValue, int yValue) {
    for (auto & cell : cells) {
        if (cell.xPosition == xValue && cell.yPosition == yValue) {
            if (!cell.hasFlag) {
                cell.hasFlag = true;
                counterNum--;
            } else if (cell.hasFlag) {
                cell.hasFlag = false;
                counterNum++;
            }
            break;
        }
    }
}

// looks through the vector of cells to see which one the user clicked on, and changing to revealed variable to true
void Board::placeRevealedTile(int xValue, int yValue) {
    for (auto & cell : cells) {
        if (cell.xPosition == xValue && cell.yPosition == yValue) {
            cell.isRevealed = true;
            break;
        }
    }
}

void Board::resetBoard() {
    currFace = happyFace;

    for (auto & cell : cells) {
        cell.isRevealed = false;
        cell.hasFlag = false;
        cell.hasBomb = false;
    }
    generatedRandom = false;
    generateBombs();
}

// randomly generates the bombs in the board;
void Board::generateBombs() {
    if (!generatedRandom) {
        for (int i = 0; i < bombCount; i++) {
            int randInt = rand() % cells.size();

            while (cells[randInt].hasBomb) {
                randInt = rand() % cells.size();
            }
            cells[randInt].hasBomb = true;
        }
        generatedRandom = true;
    }
}

void Board::allRevealed() {
    prevCells.resize(cells.size());

    for (int i = 0; i < cells.size(); i++) {
        prevCells[i] = cells[i];

        cells[i].hasFlag = false;
        cells[i].hasBomb = false;
        cells[i].isRevealed = true;
    }
}

void Board::previousState() {
    for (int i = 0; i < prevCells.size(); i++) {
        cells[i] = prevCells[i];
    }
}

void Board::findAdjacentCells(int index) {
    Cell& currCell = cells[index];
    currCell.surroundingCells.clear();

    if (index % colCount == 0) {
        if (index < colCount) {
            currCell.surroundingCells.push_back(&cells[index + 1]);
            currCell.surroundingCells.push_back(&cells[index + colCount]);
            currCell.surroundingCells.push_back(&cells[index + colCount + 1]);
        }

        else if (index >= cells.size() - colCount) {
            currCell.surroundingCells.push_back(&cells[index - colCount]);
            currCell.surroundingCells.push_back(&cells[index - colCount + 1]);
            currCell.surroundingCells.push_back(&cells[index + 1]);
        }

        else {
            currCell.surroundingCells.push_back(&cells[index - colCount]);
            currCell.surroundingCells.push_back(&cells[index - colCount + 1]);
            currCell.surroundingCells.push_back(&cells[index + 1]);
            currCell.surroundingCells.push_back(&cells[index + colCount]);
            currCell.surroundingCells.push_back(&cells[index + colCount + 1]);
        }
    }

    else if (index % colCount == colCount - 1) {
        if (index < colCount) {
            currCell.surroundingCells.push_back(&cells[index - 1]);
            currCell.surroundingCells.push_back(&cells[index + colCount]);
            currCell.surroundingCells.push_back(&cells[index + colCount - 1]);
        }

        else if (index >= cells.size() - colCount) {
            currCell.surroundingCells.push_back(&cells[index - colCount]);
            currCell.surroundingCells.push_back(&cells[index - colCount - 1]);
            currCell.surroundingCells.push_back(&cells[index - 1]);
        }

        else {
            currCell.surroundingCells.push_back(&cells[index - colCount]);
            currCell.surroundingCells.push_back(&cells[index - colCount - 1]);
            currCell.surroundingCells.push_back(&cells[index - 1]);
            currCell.surroundingCells.push_back(&cells[index + colCount]);
            currCell.surroundingCells.push_back(&cells[index + colCount - 1]);
        }
    }

    else {
        if (index < colCount) {
            currCell.surroundingCells.push_back(&cells[index - 1]);
            currCell.surroundingCells.push_back(&cells[index + 1]);
            currCell.surroundingCells.push_back(&cells[index + colCount]);
            currCell.surroundingCells.push_back(&cells[index + colCount - 1]);
            currCell.surroundingCells.push_back(&cells[index + colCount + 1]);
        }

        else if (index > cells.size() - colCount) {
            currCell.surroundingCells.push_back(&cells[index - colCount - 1]);
            currCell.surroundingCells.push_back(&cells[index - colCount]);
            currCell.surroundingCells.push_back(&cells[index - colCount + 1]);
            currCell.surroundingCells.push_back(&cells[index - 1]);
            currCell.surroundingCells.push_back(&cells[index + 1]);
        }

        else {
            currCell.surroundingCells.push_back(&cells[index - colCount - 1]);
            currCell.surroundingCells.push_back(&cells[index - colCount]);
            currCell.surroundingCells.push_back(&cells[index - colCount + 1]);
            currCell.surroundingCells.push_back(&cells[index - 1]);
            currCell.surroundingCells.push_back(&cells[index + 1]);
            currCell.surroundingCells.push_back(&cells[index + colCount]);
            currCell.surroundingCells.push_back(&cells[index + colCount - 1]);
            currCell.surroundingCells.push_back(&cells[index + colCount + 1]);
        }
    }
}

void Board::findBombs(int index) {
    Cell& currCell = cells[index];

    int bombs = 0;
    for (int i = 0; i < currCell.surroundingCells.size(); i++) {
        if (currCell.surroundingCells[i]->hasBomb) {
            bombs++;
        }
    }
    currCell.numBombs = bombs;
}

void Board::displayEmptyCells(int index) {
    if (cells[index].numBombs == 0) {
        for (int i = 0; i < cells[index].surroundingCells.size(); i++) {
            if (!cells[index].hasBomb) {
                if (!cells[index].surroundingCells[i]->hasFlag) {
                    cells[index].surroundingCells[i]->isRevealed = true;
                }
            }
        }
    }
}

void Board::checkIfWinner() {
    int revealedCount;
    for (int i = 0; i < cells.size(); i ++) {
        if ((cells[i].isRevealed || cells[i].hasFlag) && !cells[i].hasBomb ) {
            revealedCount++;
        }
    }
    if (revealedCount == cells.size() - bombCount) {
        gameWon = true;
    }
}

std::map<int, sf::Sprite> Board::parseDigits(sf::Sprite digits) {
    std::map<int, sf::Sprite> digitsMap;

    for (int i = 0; i < 10; i++) {
        sf::IntRect rect(i * 21, 0, 21, 32);
        digits.setTextureRect(rect);
        sf::Sprite sprite = digits;
        digitsMap.emplace(i, sprite);
    }

    return digitsMap;
}