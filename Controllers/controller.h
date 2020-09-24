#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Renderers/Renderer.h"
#include "Logic/Tetris.h"
#include <vector>


class Controller
{
public:
    enum MOVEMENT{
        MOVE_LEFT,
        MOVE_RIGHT,
        ROTATE,
        SPEED_UP
    };
private:
    std::vector<MOVEMENT> m_movementQueue;

    Renderer *m_renderer;
    Tetris *m_logic;
    int m_maxSpeed = 20;
    int m_speedCounter = 0;

public:
    Controller();
    void pullMoveLeft();
    void pullMoveRight();
    void pullRotate();
    void pullSpeedUp();

    void draw();


    void start();
    void setRenderer(Renderer *renderer);
    Renderer *getRenderer() const;
};

#endif // CONTROLLER_H
