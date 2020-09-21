#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSurfaceFormat format;
    format.setVersion(4,1);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
    this->ui->openGLWidget->setFormat(format);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:  std::cout << "Tecla esquerda" << std::endl;
            m_controller.pullMoveLeft();
    break;

    case Qt::Key_Right:// std::cout << "Tecla Direita" << std::endl;
            m_controller.pullMoveRight();
    break;

    case Qt::Key_Up:  //  std::cout << "Tecla Cima" << std::endl;
            m_controller.pullRotate();
    break;

    case Qt::Key_Down://  std::cout << "Tecla baixo" << std::endl;
            m_controller.pullSpeedUp();
    break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    m_controller.setRenderer(ui->openGLWidget);
    m_controller.start();
}
