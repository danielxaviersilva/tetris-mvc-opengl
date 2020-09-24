#ifndef TETRIS_H
#define TETRIS_H
#include <vector>
#include <glm/glm.hpp>
#include <time.h>

#define TETROMINO_AMOUNT 7
#define FIELD_WIDTH 12
#define FIELD_HEIGHT 18
#define BORDER 7
#define EMPTY_SPACE -1


class Tetris
{
public:
    enum rotationAngles{
        CASE0, CASE90, CASE180, CASE270
    };
private:


    std::vector<int> m_tetrominoSet[TETROMINO_AMOUNT];
    std::vector<int> m_currentTetromino;

    std::vector<int> m_logicField;
    std::vector<int> m_renderField;
    std::vector<glm::vec2> m_centerSet;

    std::vector<glm::vec2> m_currentCenters;
    std::vector<float> m_currentTetrominoIndex;
    int m_currentTetrominoPosition[2];
    int m_currentIndex;

public:
    Tetris();
    void generateTetromino();
    int getFieldWidth();
    int getFieldHeight();

    std::vector<glm::vec2> & getCurrentCenters();
    std::vector<float>& getTetrominoIndex();

    void moveLeft();
    void moveRight();
    void moveDown();
    void Rotate(rotationAngles rotation);
    void rotate90();
    void forcePieceDown();

private:
    bool pieceFits(rotationAngles rotationAngle, int posX, int posY);
    int rotatePosition(int px, int py, rotationAngles rotationAngle);
    void clearTetromino();
    void updateField();

    void lockedPieceHandler();
};

#endif // TETRIS_H
