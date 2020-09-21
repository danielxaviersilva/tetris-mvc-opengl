#include "Tetris.h"

Tetris::Tetris()
{
    srand(time(NULL));
    m_tetrominoSet[0] = {0,0,1,0,
                         0,0,1,0,
                         0,0,1,0,
                         0,0,1,0};

    m_tetrominoSet[1] = {0,0,1,0,
                         0,1,1,0,
                         0,1,0,0,
                         0,0,0,0};

    m_tetrominoSet[2] = {0,1,0,0,
                         0,1,1,0,
                         0,0,1,0,
                         0,0,0,0};

    m_tetrominoSet[3] = {0,0,0,0,
                         0,1,1,0,
                         0,1,1,0,
                         0,0,0,0};

    m_tetrominoSet[4] = {0,0,1,0,
                         0,1,1,0,
                         0,0,1,0,
                         0,0,0,0};

    m_tetrominoSet[5] = {0,0,0,0,
                         0,1,1,0,
                         0,0,1,0,
                         0,0,1,0};

    m_tetrominoSet[6] = {0,0,0,0,
                         0,1,1,0,
                         0,1,0,0,
                         0,1,0,0};

    for(int j = 0; j < FIELD_HEIGHT; j++)
        for(int i = 0; i < FIELD_WIDTH; i++)
            if(i == 0 || i == FIELD_WIDTH -1 || j == FIELD_HEIGHT-1)
                m_field.push_back(BORDER);
            else
                m_field.push_back(rand()%BORDER);

    std::vector<float> borderMeshX;
    std::vector<float> borderMeshY;

    for(float i = -1; i <= 1.01; i+=(2/float(FIELD_WIDTH)))
                borderMeshX.push_back(i);

    for(float j = 1; j >= -1.01; j-=2/float(FIELD_HEIGHT))
            borderMeshY.push_back(j);


    for(int j = 0; j < FIELD_HEIGHT; j++)
        for(int i = 0; i < FIELD_WIDTH; i++)
            m_centerSet.push_back(glm::vec2(0.5f*(borderMeshX[i] + borderMeshX[i+1]), 0.5f*(borderMeshY[j] + borderMeshY[j+1])));
}

void Tetris::generateTetromino()
{
    m_currentTetromino = m_tetrominoSet[rand()%BORDER];
}

int Tetris::getFieldWidth()
{
    return FIELD_WIDTH;
}

int Tetris::getFieldHeight()
{
    return FIELD_HEIGHT;
}

std::vector<glm::vec2> Tetris::getCurrentCenters()
{
    std::vector<glm::vec2> currentCenters;

    for (int i = 0; i < FIELD_WIDTH*FIELD_HEIGHT; i++)
        if(m_field[i] != EMPTY_SPACE)
            currentCenters.push_back(m_centerSet[i]);

    return  currentCenters;

}

std::vector<float> Tetris::getTetrominoIndex()
{
    std::vector<float> currentTetrominoIndex;

    for (int i = 0; i < FIELD_WIDTH*FIELD_HEIGHT; i++)
        if(m_field[i] != EMPTY_SPACE)
            currentTetrominoIndex.push_back((float)m_field[i]);

    return currentTetrominoIndex;

}
