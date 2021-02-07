#include "PieceRenderer.h"

PieceRenderer::PieceRenderer(QWidget *parent): QOpenGLWidget{parent}
{
        QSurfaceFormat format;
        format.setVersion(4,1);
        format.setRenderableType(QSurfaceFormat::OpenGL);
        format.setProfile(QSurfaceFormat::CoreProfile);
        format.setDepthBufferSize(24);
        QSurfaceFormat::setDefaultFormat(format);
        this->setFormat(format);
}

void PieceRenderer::initializeGL()
{

}

void PieceRenderer::paintGL()
{
    if (m_controller == nullptr)
        return;
    //Game Timing


    //Input

    //Game Logic

    //renderer
        m_controller->drawNextPiece();
        update();
//        setScore(m_controller->getTetrisScore());
//        setHorizontalLine(m_controller->getTetrisHorizontalLines());
//        setPieceCounter(m_controller->getPieceCounter());
}

Controller *PieceRenderer::getController() const
{
    return m_controller;
}

void PieceRenderer::setController(Controller *controller)
{
    m_controller = controller;
}
