#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Renderers/Renderer.h"
#include "Logic/Tetris.h"

#include <chrono>
#include <thread>
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
    int m_maxSpeed;
    int m_speedCounter;

public:
    Controller();
    ~Controller();
    void pullMoveLeft();
    void pullMoveRight();
    void pullRotate();
    void pullSpeedUp();

    std::string getTetrisScore() const;
    std::string getTetrisHorizontalLines() const;
    std::string getPieceCounter() const;

    void draw();


    void start();
    void setRenderer(Renderer *renderer);
    Renderer *getRenderer() const;
};

#endif // CONTROLLER_H
