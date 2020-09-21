#include "controller.h"

void Controller::setRenderer(Renderer *renderer)
{
    m_renderer = renderer;
}

Controller::Controller(Renderer* renderer): m_logic(nullptr), m_renderer(renderer)
{

}

void Controller::pullMoveLeft()
{
    m_movementQueue.push_back(MOVE_LEFT);

}

void Controller::pullMoveRight()
{
     m_movementQueue.push_back(MOVE_RIGHT);
}

void Controller::pullRotate()
{
     m_movementQueue.push_back(ROTATE);
}

void Controller::pullSpeedUp()
{
    m_movementQueue.push_back(SPEED_UP);
}

void Controller::start()
{
    m_logic = new Tetris;
    m_renderer->initialize(m_logic);
//    while(1)
        m_renderer->render();
}
