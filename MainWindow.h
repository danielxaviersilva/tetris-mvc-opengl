#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "Controllers/controller.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Controller * m_controller;
    int m_score;

    const int m_timerLength;

    QTimer* m_gameTimer;


protected:
    void keyPressEvent(QKeyEvent* event) override;

public slots:
    void UpdateGame();


};
#endif // MAINWINDOW_H
