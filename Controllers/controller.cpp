#include "controller.h"

Controller::Controller(): m_boardRenderer(nullptr),  m_NextPieceRenderer(nullptr), m_logic(nullptr), m_maxSpeed(30), m_speedCounter(0)
{}

Controller::~Controller()
{
    delete m_logic;
    delete m_boardRenderer;
    delete m_NextPieceRenderer;
}


Renderer *Controller::getRenderer() const{
    return m_boardRenderer;
}


void Controller::pullMoveLeft(){
    if( m_logic == nullptr )
        return;
    m_logic->moveLeft();
}

void Controller::pullMoveRight(){
    if( m_logic != nullptr ){
        if ( !m_logic->IsGameOver() ){
            m_logic->moveRight();
        }
    }
}

void Controller::pullRotate(){
    if( m_logic != nullptr ){
        if ( !m_logic->IsGameOver() ){
           m_logic->rotate90();
        }
    }

}

void Controller::pullSpeedUp(){
    if( m_logic == nullptr )
        return;
    m_logic->moveDown();
}

std::string Controller::getTetrisScore() const{
    if(m_logic != nullptr)
        return std::to_string(m_logic->getScore());
    else
        return std::string("");
}

std::string Controller::getTetrisHorizontalLines() const
{

    if(m_logic != nullptr)
        return std::to_string(m_logic->getHorizontalLinesCounter());
    else
        return std::string("");

}

std::string Controller::getPieceCounter() const
{
    if(m_logic != nullptr)
        return std::to_string(m_logic->getPieceCounter());
    else
        return std::string("");

}

void Controller::drawBoard(){
    if( m_boardRenderer == nullptr || m_logic == nullptr )
        return;
//   std::this_thread::sleep_for(std::chrono::milliseconds(25));
   m_logic->movementHandler();
    m_boardRenderer->render(m_logic->GetTetrominoIndex());

}

void Controller::drawNextPiece()
{
    if( m_NextPieceRenderer == nullptr || m_logic == nullptr )
        return;
//   std::this_thread::sleep_for(std::chrono::milliseconds(25));
//   m_logic->movementHandler();
   m_NextPieceRenderer->render(m_logic->getNextTetromino());

}

void Controller::start()
{
    if(m_logic != nullptr)
        delete m_logic;

    m_logic = new Tetris;
    m_boardRenderer = new Renderer;
    m_boardRenderer->initialize(m_logic->GetFieldWidth(), m_logic->GetFieldHeight());
    m_NextPieceRenderer = new Renderer(true);
    m_NextPieceRenderer->initialize(4, 4);

}
