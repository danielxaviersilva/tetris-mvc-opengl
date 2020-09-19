#include "controller.h"

Controller::Controller()
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
