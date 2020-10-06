#include "controller.h"

Controller::Controller(): m_renderer(nullptr),  m_logic(nullptr)
{}


Renderer *Controller::getRenderer() const
{
    return m_renderer;
}



void Controller::pullMoveLeft(){
    m_logic->moveLeft();
}

void Controller::pullMoveRight(){
     m_logic->moveRight();
}

void Controller::pullRotate(){
    m_logic->rotate90();
}

void Controller::pullSpeedUp(){
    m_logic->moveDown();
}

int Controller::getTetrisScore() const{
    if(m_logic != nullptr)
        return m_logic->getScore();
    else
        return 0;
}

std::string Controller::getTetrisHorizontalLines() const
{

    if(m_logic != nullptr){
        auto temp = m_logic->getHorizontalLinesCounter();
        return std::to_string(m_logic->getHorizontalLinesCounter());}
    else
        return std::string("");

}

void Controller::draw(){
    if(m_renderer == nullptr || m_logic == nullptr)
        return;
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
   m_logic->movementHandler();
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
