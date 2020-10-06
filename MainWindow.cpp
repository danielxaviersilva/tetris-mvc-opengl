#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_score(0)
{
    ui->setupUi(this);
    QSurfaceFormat format;
    format.setVersion(4,1);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
    this->ui->openGLWidget->setFormat(format);

    m_controller = new Controller;
    this->ui->openGLWidget->setController(m_controller);

    connect(this->ui->openGLWidget, SIGNAL(scoreChanged(int)),
            ui->ScoreValue, SLOT(setNum(int)));

    connect(this->ui->openGLWidget, SIGNAL(horizontalLineChanged(QString)),
            ui->HorizontalLinesValue, SLOT(setText(QString)));




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
//    std::cout << __FUNCTION__ << std::endl;
    switch(event->key())
    {
    case Qt::Key_Left:  //std::cout << "Tecla esquerda" << std::endl;
            m_controller->pullMoveLeft();
    break;

    case Qt::Key_Right: //std::cout << "Tecla Direita" << std::endl;
            m_controller->pullMoveRight();
    break;

    case Qt::Key_Up:  //  std::cout << "Tecla Cima" << std::endl;
            m_controller->pullRotate();
    break;

    case Qt::Key_Down://  std::cout << "Tecla baixo" << std::endl;
            m_controller->pullSpeedUp();
    break;
    }

}


void MainWindow::on_pushButton_clicked()
{
    m_controller->start();
    m_controller = ui->openGLWidget->getController();
}
