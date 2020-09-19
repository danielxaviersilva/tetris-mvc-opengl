#ifndef TETRIS_H
#define TETRIS_H
#include <vector>
#include <glm/glm.hpp>
#include <time.h>

#define FIELD_WIDTH 5
#define FIELD_HEIGHT 10
#define BORDER 7


class Tetris
{
    std::vector<int> m_tetrominoSet[7];
    std::vector<int> m_currentTetromino;

    std::vector<int> m_field;
    std::vector<glm::vec2> m_centerSet;

public:
    Tetris();
    void generateTetromino();
    int getFieldWidth();
    int getFieldHeight();
};

#endif // TETRIS_H
