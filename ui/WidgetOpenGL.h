#ifndef QGLWIDGET_H
#define QGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QString>



#include "../Renderers/Renderer.h"
#include "Controllers/controller.h"


class WidgetOpenGL: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
     WidgetOpenGL(QWidget *parent = nullptr);
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    void start();
    Controller *getController() const;

    void setController(Controller *controller);

private:
   Controller *m_controller;

   int m_score;
   std::string m_horizontalLineCount;

signals:
   void scoreChanged(int score);
   void horizontalLineChanged(QString horizontalLine);

public slots:
   void setScore(int score);
   void setHorizontalLine(std::string horizontalLine);



};



#endif // QGLWIDGET_H
