#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "Controllers/controller.h"

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


protected:
    void keyPressEvent(QKeyEvent* event) override;


};
#endif // MAINWINDOW_H
