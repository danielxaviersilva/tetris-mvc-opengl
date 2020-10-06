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

   std::string m_score;
   std::string m_horizontalLineCount;
   std::string m_pieceCounter;

public slots:
   void setScore(std::string score);
   void setHorizontalLine(std::string horizontalLine);
   void setPieceCounter(std::string pieceCounter);

signals:
   void scoreChanged(QString score);
   void horizontalLineChanged(QString horizontalLine);
   void pieceCounterChanged(QString pieceCounter);





};

#endif // QGLWIDGET_H
