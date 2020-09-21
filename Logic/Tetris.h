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
    std::vector<int> m_tetrominoSet[TETROMINO_AMOUNT];
    std::vector<int> m_currentTetromino;

    std::vector<int> m_field;
    std::vector<glm::vec2> m_centerSet;

public:
    Tetris();
    void generateTetromino();
    int getFieldWidth();
    int getFieldHeight();

    std::vector<glm::vec2> getCurrentCenters();
    std::vector<float> getTetrominoIndex();
};

#endif // TETRIS_H
