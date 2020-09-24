#include "WidgetOpenGL.h"

WidgetOpenGL::WidgetOpenGL(QWidget *parent): QOpenGLWidget{parent}
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
    //Game Timing
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    //Input

    //Game Logic

    //renderer
        m_controller->draw();
        update();

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

