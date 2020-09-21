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

public:
    Controller(Renderer* renderer = nullptr);
    void pullMoveLeft();
    void pullMoveRight();
    void pullRotate();
    void pullSpeedUp();


    void start();
    void setRenderer(Renderer *renderer);
};

#endif // CONTROLLER_H
