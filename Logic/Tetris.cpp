#include "Tetris.h"
#include <iostream>

Tetris::Tetris(int fieldWidth, int fieldHeight): m_fieldWidth(fieldWidth), m_fieldHeight(fieldHeight)
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

    m_tetrominoSet[3] = {0,1,1,0,
                         0,1,1,0,
                         0,0,0,0,
                         0,0,0,0};

    m_tetrominoSet[4] = {0,0,1,0,
                         0,1,1,0,
                         0,0,1,0,
                         0,0,0,0};

    m_tetrominoSet[5] = {0,1,1,0,
                         0,0,1,0,
                         0,0,1,0,
                         0,0,0,0};

    m_tetrominoSet[6] = {0,1,1,0,
                         0,1,0,0,
                         0,1,0,0,
                         0,0,0,0};

    for(int j = 0; j < m_fieldHeight; j++)
        for(int i = 0; i < m_fieldWidth; i++)
            if(i == 0 || i == m_fieldWidth -1 || j == m_fieldHeight-1)
                m_logicField.push_back(BORDER);
            else{
                m_logicField.push_back(EMPTY_SPACE);
            }

    m_renderField = m_logicField;


    std::vector<float> borderMeshX;
    std::vector<float> borderMeshY;

    for(float i = -1; i <= 1.01; i+=(2/float(m_fieldWidth)))
        borderMeshX.push_back(i);

    for(float j = 1; j >= -1.01; j-=2/float(m_fieldHeight))
        borderMeshY.push_back(j);


    for(int j = 0; j < m_fieldHeight; j++)
        for(int i = 0; i < m_fieldWidth; i++)
            m_centerSet.push_back(glm::vec2(0.5f*(borderMeshX[i] + borderMeshX[i+1]), 0.5f*(borderMeshY[j] + borderMeshY[j+1])));


    generateTetromino();
    m_currentTetrominoPosition[0] = 0;
    m_currentTetrominoPosition[1] = 0;

    updateField();
}

void Tetris::generateTetromino()
{
//    srand(time(NULL));
    int genIndex = rand()%TETROMINO_AMOUNT;
    m_currentTetromino = m_tetrominoSet[genIndex];
    m_currentIndex = genIndex;
}

int Tetris::getFieldWidth()
{
    return m_fieldWidth;
}

int Tetris::getFieldHeight()
{
    return m_fieldHeight;
}

std::vector<glm::vec2>& Tetris::getCurrentCenters()
{
    m_currentCenters.clear();
    for (int i = 0; i < m_fieldWidth*m_fieldHeight; i++)
        if(m_renderField[i] != EMPTY_SPACE)
            m_currentCenters.push_back(m_centerSet[i]);

    return  m_currentCenters;

}

std::vector<float>& Tetris::getTetrominoIndex()
{
    m_currentTetrominoIndex.clear();
    for (int i = 0; i < m_fieldWidth*m_fieldHeight; i++)
        if(m_renderField[i] != EMPTY_SPACE)
            m_currentTetrominoIndex.push_back((float)m_renderField[i]);

    return m_currentTetrominoIndex;

}

void Tetris::moveLeft()
{
    if(pieceFits(CASE0, m_currentTetrominoPosition[0]-1, m_currentTetrominoPosition[1])){
        clearTetromino();
        m_currentTetrominoPosition[0]--;
        updateField();
    }

}

void Tetris::moveRight()
{
        if(pieceFits(CASE0, m_currentTetrominoPosition[0]+1, m_currentTetrominoPosition[1])){
            clearTetromino();
            m_currentTetrominoPosition[0]++;
            updateField();
        }
}

void Tetris::moveDown()
{
    if(pieceFits(CASE0, m_currentTetrominoPosition[0], m_currentTetrominoPosition[1]+1)){
        clearTetromino();
        m_currentTetrominoPosition[1]++;
        updateField();
    }
    else{
        lockedPieceHandler();
    }

}

void Tetris::Rotate(Tetris::rotationAngles rotation)
{
    std::vector<int> rotatedTetromino;
    rotatedTetromino.resize(16);
    for(int py = 0; py < 4; py++)
    {
        for (int px = 0; px < 4; px++)
        {
        switch(rotation){
            case CASE0:   rotatedTetromino[px + 4*py] = m_currentTetromino[py*4 + px     ];break;
            case CASE90:  rotatedTetromino[px + 4*py] = m_currentTetromino[12 + py - px*4];break;
            case CASE180: rotatedTetromino[px + 4*py] = m_currentTetromino[15 - py*4 -px ];break;
            case CASE270: rotatedTetromino[px + 4*py] = m_currentTetromino[3- py + px*4  ];break;
        }
        }
    }
    m_currentTetromino = rotatedTetromino;
}

void Tetris::rotate90()
{
    if(pieceFits(CASE90, m_currentTetrominoPosition[0], m_currentTetrominoPosition[1]+1)){
        clearTetromino();
        Rotate(CASE90);
        updateField();
    }

}

void Tetris::forcePieceDown()
{
    if(pieceFits(CASE0, m_currentTetrominoPosition[0], m_currentTetrominoPosition[1]+1)){
        clearTetromino();
        m_currentTetrominoPosition[1]++;
        updateField();
    }
    else
        lockedPieceHandler();


}

bool Tetris::pieceFits(Tetris::rotationAngles rotationAngle, int posX, int posY)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j =0; j<4; j++)
        {
            int blockPosition = rotatePosition(i, j, rotationAngle);
            int fieldBlockPosition = (posY + j)*m_fieldWidth + (posX + i);

            if(posX + i >= 0 && posX + i <= m_fieldWidth)
            {
                if(posY + j>=0 && posY + j <= m_fieldHeight)
                {
                    if(m_currentTetromino[blockPosition] !=0 && m_logicField[fieldBlockPosition] != EMPTY_SPACE)
                        return false;
                }
            }
        }
    }

    return true;
}

int Tetris::rotatePosition(int px, int py, rotationAngles rotationAngle)
{
    switch (rotationAngle)
    {
        case CASE0:   return py*4 + px;
        case CASE90:  return 12 + py - px*4;
        case CASE180: return 15 - py*4 -px;
        case CASE270: return 3 - py + px*4;
    }
    return 0;
}

void Tetris::clearTetromino()
{
    for (int i = 0; i<4;i++){
        for(int j = 0; j<4;j++){
            if(m_currentTetromino[i+ 4*j] != 0)
                m_renderField[i + m_currentTetrominoPosition[0] + (j+ m_currentTetrominoPosition[1])*m_fieldWidth] = EMPTY_SPACE;
        }
    }
}

void Tetris::updateField()
{
    for (int i = 0; i<4;i++)
        for(int j = 0; j<4;j++)
            if(m_currentTetromino[i + j*4] == 1)
                m_renderField[i + m_currentTetrominoPosition[0] + (j+ m_currentTetrominoPosition[1])*m_fieldWidth] = m_currentIndex;

}

void Tetris::lockedPieceHandler()
{
//    m_logicField = m_renderField;

    for (int j  = 0; j < m_fieldHeight-1; j++)
    {
        int rowCounter = 0;
        for (int i = 1; i< m_fieldWidth -1; i++)
            if(m_renderField[j*m_fieldWidth + i] != EMPTY_SPACE)
                rowCounter++;
            else break;
        if(rowCounter == m_fieldWidth - 2){
            for (int k = j; k>0; k--)
                for (int i = 1; i< m_fieldWidth-1; i++) //In this case, conserving the borders
                    m_renderField[k*m_fieldWidth + i] = m_renderField[(k-1)*m_fieldWidth + i];
        }
    }

    m_logicField = m_renderField;

    generateTetromino();
    m_currentTetrominoPosition[0] = rand()%TETROMINO_AMOUNT;
    m_currentTetrominoPosition[1] = 0;
    if(!pieceFits(CASE90, m_currentTetrominoPosition[0], m_currentTetrominoPosition[1]))
        std::cout << "game over" << std::endl;


}
