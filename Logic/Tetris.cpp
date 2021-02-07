#include "Tetris.h"
#include <iostream>



Tetris::Tetris(int fieldWidth, int fieldHeight): m_fieldWidth(fieldWidth), m_fieldHeight(fieldHeight), m_speedIncreaseRate(7), m_maximumSpeedRate(15),
    m_maxSpeed(40), m_speedCounter(0), m_pieceCounter(0), m_horizontalLinesCounter(0), m_speedIncreaseCheck(false), m_isGameOver(false), m_score(0)
{
    srand(time(NULL));
    m_tetrominoSet[0] = {0,0,1,0,
                         0,0,1,0,
                         0,0,1,0,
                         0,0,1,0};

    m_tetrominoSet[1] = {1,1,0,0,
                         0,1,1,0,
                         0,0,0,0,
                         0,0,0,0};

    m_tetrominoSet[2] = {0,0,1,1,
                         0,1,1,0,
                         0,0,0,0,
                         0,0,0,0};

    m_tetrominoSet[3] = {0,0,0,0,
                         0,1,1,0,
                         0,1,1,0,
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

    for(int j = 0; j < m_fieldHeight; j++){
        for(int i = 0; i < m_fieldWidth; i++){
            if(i == 0 || i == m_fieldWidth -1 || j == m_fieldHeight-1){
                m_logicField.push_back(BORDER);
           } else{
                m_logicField.push_back(EMPTY_SPACE);
           }
        }
    }

    m_renderField = m_logicField;
    m_nextIndex = rand()%TETROMINO_AMOUNT;
    m_nextIndex = rand()%TETROMINO_AMOUNT; //Called 2 times just to neglet the first value, which is always the same
    m_nextTetromino = m_tetrominoSet[m_nextIndex];
    GenerateTetromino();
    resetTetrominoPosition();
    updateField();
}

void Tetris::GenerateTetromino()
{

    m_currentTetromino = m_nextTetromino;
    m_currentIndex = m_nextIndex;
    m_nextIndex = rand()%TETROMINO_AMOUNT;

    m_nextTetromino = m_tetrominoSet[m_nextIndex];

    m_pieceCounter++;

    if( !(m_pieceCounter%m_speedIncreaseRate) ){
        m_speedIncreaseCheck = true;
    }
}


void Tetris::moveLeft()
{
    if( pieceFits(CASE0, m_currentTetrominoPosition[0]-1, m_currentTetrominoPosition[1]) && !m_isGameOver ){
        clearTetromino();
        m_currentTetrominoPosition[0]--;
        updateField();
    }
}

void Tetris::moveRight()
{
        if( pieceFits(CASE0, m_currentTetrominoPosition[0]+1, m_currentTetrominoPosition[1])&& !m_isGameOver ){
            clearTetromino();
            m_currentTetrominoPosition[0]++;
            updateField();
        }
}

void Tetris::moveDown()
{
    if( pieceFits(CASE0, m_currentTetrominoPosition[0], m_currentTetrominoPosition[1]+1) && !m_isGameOver ){
        clearTetromino();
        m_currentTetrominoPosition[1]++;
        updateField();
        m_score+=2;
    } else {
        lockedPieceHandler();
    }

}

void Tetris::Rotate(Tetris::RotationAngles_t rotation)
{
    std::vector<int> rotatedTetromino;
    rotatedTetromino.resize(16);
    for(int py = 0; py < 4; py++){
        for (int px = 0; px < 4; px++) {
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
    if( pieceFits(CASE90, m_currentTetrominoPosition[0], m_currentTetrominoPosition[1]+1) ){
        clearTetromino();
        Rotate(CASE90);
        updateField();
    }
}

void Tetris::forcePieceDown()
{
    if( pieceFits(CASE0, m_currentTetrominoPosition[0], m_currentTetrominoPosition[1]+1) ){
        clearTetromino();
        m_currentTetrominoPosition[1]++;
        updateField();
        m_score++;
    }else{
        lockedPieceHandler();
    }
}

void Tetris::movementHandler()
{
    if( IsGameOver() ){
        return;
    }
    m_speedCounter++;
    if(m_speedCounter >= m_maxSpeed){
        m_speedCounter = 0;
        forcePieceDown();
    }
}

bool Tetris::pieceFits(Tetris::RotationAngles_t rotationAngle, int posX, int posY) const
{
    for (int i = 0; i < 4; i++){
        for (int j =0; j<4; j++){
            int blockPosition = rotatePosition(i, j, rotationAngle);
            int fieldBlockPosition = (posY + j)*m_fieldWidth + (posX + i);

            if( posX + i >= 0 && posX + i <= m_fieldWidth ){
                if( posY + j>=0 && posY + j <= m_fieldHeight ){
                    if(m_currentTetromino[blockPosition] !=0 && m_logicField[fieldBlockPosition] != EMPTY_SPACE){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int Tetris::rotatePosition(int px, int py, RotationAngles_t rotationAngle) const
{
    switch ( rotationAngle ){
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
            if(m_currentTetromino[i+ 4*j] != 0){
                m_renderField[i + m_currentTetrominoPosition[0] + (j+ m_currentTetrominoPosition[1])*m_fieldWidth] = EMPTY_SPACE;
            }
        }
    }
}
void Tetris::updateField()
{
    for (int i = 0; i<4;i++){
        for(int j = 0; j<4;j++){
            if(m_currentTetromino[i + j*4] == 1){
                m_renderField[i + m_currentTetrominoPosition[0] + (j+ m_currentTetrominoPosition[1])*m_fieldWidth] = (m_currentIndex+ 2);
            }
        }
    }

}

void Tetris::lockedPieceHandler()
{
    if( IsGameOver() ){
        return;
    }
    m_speedCounter = m_maxSpeed;
    GenerateTetromino();
    checkHorizontalLines();
    m_logicField = m_renderField;

    resetTetrominoPosition();
    speedHandler();

    if(!pieceFits(CASE90, m_currentTetrominoPosition[0], m_currentTetrominoPosition[1])){
        std::cout << "game over" << std::endl;
        m_isGameOver = true;
        return;
    }
}

inline void Tetris::resetTetrominoPosition()
{
    m_currentTetrominoPosition[0] = m_fieldWidth/2 -1;
    m_currentTetrominoPosition[1] = -1;
}

inline void Tetris::checkHorizontalLines()
{
    float SerialBlocksAdditionalRewardCoeff = 1.0f;
    for (int j  = 0; j < m_fieldHeight-1; j++){
        int rowCounter = 0;
        for (int i = 1; i< m_fieldWidth -1; i++){
            if(m_renderField[j*m_fieldWidth + i] != EMPTY_SPACE){
                rowCounter++;
            } else break;
        }
        if( rowCounter == m_fieldWidth - 2 ){
            m_horizontalLinesCounter++;
            m_score += int(SerialBlocksAdditionalRewardCoeff*20);
            SerialBlocksAdditionalRewardCoeff*=1.2f;
            for (int k = j; k>0; k--){
                for (int i = 1; i< m_fieldWidth-1; i++){ //In this case, conserving the borders
                    m_renderField[k*m_fieldWidth + i] = m_renderField[(k-1)*m_fieldWidth + i];
                }
            }
        }
    }
}

inline void Tetris::speedHandler()
{
    if( m_speedIncreaseCheck ){
        m_speedIncreaseCheck = false;
        if(m_maxSpeed >= m_maximumSpeedRate){
            std::cout << "Speed now: " << m_maxSpeed << std::endl;
            m_maxSpeed--;
            m_speedCounter = 0;
        }
    }
}

const int& Tetris::GetFieldWidth(){
    return m_fieldWidth;
}

const int& Tetris::GetFieldHeight(){
    return m_fieldHeight;
}

std::vector<float>& Tetris::GetTetrominoIndex(){
    return m_renderField;
}

int Tetris::getScore() const{
    return m_score;
}

bool Tetris::IsGameOver() const{
    return m_isGameOver;
}

int  Tetris::getPieceCounter() const{
    return m_pieceCounter;
}

int Tetris::getHorizontalLinesCounter() const{
    return m_horizontalLinesCounter;
}

std::vector<float> Tetris::getNextTetromino()
{
    std::vector<float> nextTetromino;
    nextTetromino.reserve(m_nextTetromino.size());
    for (auto & t : m_nextTetromino){
        nextTetromino.emplace_back(float((m_nextIndex+2)*t));
    }
    return nextTetromino;
}
