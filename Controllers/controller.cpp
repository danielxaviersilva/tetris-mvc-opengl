#include "controller.h"

Controller::Controller(): m_renderer(nullptr),  m_logic(nullptr)
{

}


Renderer *Controller::getRenderer() const
{
    return m_renderer;
}



void Controller::pullMoveLeft()
{
//    m_movementQueue.push_back(MOVE_LEFT);
    m_logic->moveLeft();

}

void Controller::pullMoveRight()
{
//     m_movementQueue.push_back(MOVE_RIGHT);
     m_logic->moveRight();
}

void Controller::pullRotate()
{
    m_logic->rotate90();
//     m_movementQueue.push_back(ROTATE);
}

void Controller::pullSpeedUp()
{
    m_movementQueue.push_back(SPEED_UP);
    m_logic->moveDown();
}

void Controller::draw()
{
    if(m_renderer == nullptr)
        return;

    m_speedCounter++;
    if(m_speedCounter == m_maxSpeed)
    {
        m_speedCounter = 0;
        m_logic->forcePieceDown();
    }
    m_renderer->render(m_logic->getTetrominoIndex());

}

void Controller::start()
{
    m_logic = new Tetris;
    m_renderer = new Renderer;
    m_renderer->initialize(m_logic->getFieldWidth(), m_logic->getFieldHeight());
//    while(1)
//        m_renderer->render();
}
