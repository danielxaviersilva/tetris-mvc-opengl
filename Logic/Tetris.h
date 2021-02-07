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
    enum RotationAngles_t{
        CASE0, CASE90, CASE180, CASE270
    };
private:
    const int m_fieldWidth;
    const int m_fieldHeight;
    const int m_speedIncreaseRate;
    const int m_maximumSpeedRate;

    std::vector<int> m_tetrominoSet[TETROMINO_AMOUNT];
    std::vector<int> m_currentTetromino;
    std::vector<int> m_nextTetromino;

    std::vector<float> m_logicField;
    std::vector<float> m_renderField;

    std::vector<float> m_currentTetrominoIndex;
    int m_currentTetrominoPosition[2];
    int m_currentIndex;
    int m_nextIndex;



    int m_maxSpeed;
    int m_speedCounter;
    int m_pieceCounter;
    int m_horizontalLinesCounter;

    bool m_speedIncreaseCheck;
    bool m_isGameOver;

    int m_score;

public:
    Tetris(int fieldWidth = 12, int fieldHeight = 18);
    void GenerateTetromino();
    const int & GetFieldWidth();
    const int & GetFieldHeight();
    std::vector<float>& GetTetrominoIndex();

    void moveLeft();
    void moveRight();
    void moveDown();
    void Rotate(RotationAngles_t rotation);
    void rotate90();
    void forcePieceDown();

    void movementHandler();

    int getScore() const;

    bool IsGameOver() const;

    int getPieceCounter() const;
    int getHorizontalLinesCounter() const;

    std::vector<float> getNextTetromino();

private:
    bool pieceFits(RotationAngles_t rotationAngle, int posX, int posY) const;
    int rotatePosition(int px, int py, RotationAngles_t rotationAngle) const;
    void clearTetromino();
    void updateField();

    void lockedPieceHandler();
    inline void resetTetrominoPosition();
    inline void checkHorizontalLines();

    inline void speedHandler();
};

#endif // TETRIS_H
