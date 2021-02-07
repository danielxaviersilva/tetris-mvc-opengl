#ifndef PIECERENDERER_H
#define PIECERENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QString>


#include "../Renderers/Renderer.h"
#include "Controllers/controller.h"


class PieceRenderer: public QOpenGLWidget, protected QOpenGLFunctions
{
      Q_OBJECT
public:
    PieceRenderer(QWidget *parent = nullptr);
   void initializeGL() override;
//   void resizeGL(int width, int height) override;
   void paintGL() override;

   void start();

   Controller *getController() const;
   void setController(Controller *getController);

private:
     Controller *m_controller;
};

#endif // PIECERENDERER_H
