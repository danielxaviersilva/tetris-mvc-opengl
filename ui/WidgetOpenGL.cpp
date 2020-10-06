#include "WidgetOpenGL.h"

WidgetOpenGL::WidgetOpenGL(QWidget *parent): QOpenGLWidget{parent}, m_score(std::string("")), m_horizontalLineCount(std::string("")), m_pieceCounter(std::string(""))
{
    QSurfaceFormat format;
    format.setVersion(4,1);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
    this->setFormat(format);




}

void WidgetOpenGL::initializeGL()
{
    srand(time(NULL));
}

void WidgetOpenGL::resizeGL(int width, int height)
{

}

void WidgetOpenGL::paintGL()
{
    if (m_controller == nullptr)
        return;
    //Game Timing


    //Input

    //Game Logic

    //renderer
        m_controller->draw();
        update();
        setScore(m_controller->getTetrisScore());
        setHorizontalLine(m_controller->getTetrisHorizontalLines());
        setPieceCounter(m_controller->getPieceCounter());

}

void WidgetOpenGL::start()
{

}

Controller *WidgetOpenGL::getController() const
{
    return m_controller;
}



void WidgetOpenGL::setController(Controller *controller)
{
    m_controller = controller;
}

//void WidgetOpenGL::scoreChanged(int score)
//{

//}

void WidgetOpenGL::setScore(std::string score)
{
    if(m_score != score){
        m_score = score;
        emit scoreChanged(QString::fromStdString(m_score));
    }


}

void WidgetOpenGL::setHorizontalLine(std::string horizontalLine)
{
    if(m_horizontalLineCount != horizontalLine){
        m_horizontalLineCount = horizontalLine;
        emit horizontalLineChanged(QString::fromStdString(m_horizontalLineCount));
    }

}

void WidgetOpenGL::setPieceCounter(std::string pieceCounter)
{
    if(m_pieceCounter != pieceCounter){
        m_pieceCounter = pieceCounter;
        emit pieceCounterChanged(QString::fromStdString(m_pieceCounter));
    }

}

