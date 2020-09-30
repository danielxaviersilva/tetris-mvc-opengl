#ifndef TETRIS_H
#define TETRIS_H
#include <vector>
#include <glm/glm.hpp>
#include <time.h>

#define TETROMINO_AMOUNT 7
#define BORDER 1
#define EMPTY_SPACE 0



class Tetris
{
public:
    enum rotationAngles{
        CASE0, CASE90, CASE180, CASE270
    };
private:

    std::vector<int> m_tetrominoSet[TETROMINO_AMOUNT];
    std::vector<int> m_currentTetromino;

    std::vector<float> m_logicField;
    std::vector<float> m_renderField;
    std::vector<glm::vec2> m_centerSet;

    std::vector<glm::vec2> m_currentCenters;
    std::vector<float> m_currentTetrominoIndex;
    int m_currentTetrominoPosition[2];
    int m_currentIndex;

    int m_fieldWidth;
    int m_fieldHeight;


    int m_maxSpeed;
    int m_speedCounter;
    int m_pieceCounter;

public:
    Tetris(int fieldWidth = 12, int fieldHeight = 18);
    void generateTetromino();
    int getFieldWidth();
    int getFieldHeight();

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
    inline void resetTetrominoPosition();
};

#endif // TETRIS_H
