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

    Renderer *m_boardRenderer;
    Renderer *m_NextPieceRenderer;
    Tetris *m_logic;
    const int m_maxSpeed;
    const int m_speedCounter;

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

    void drawBoard();
    void drawNextPiece();


    void start();
    void setRenderer(Renderer *renderer);
    Renderer *getRenderer() const;
};

#endif // CONTROLLER_H
