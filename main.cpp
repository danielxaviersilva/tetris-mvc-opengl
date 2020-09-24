#include "MainWindow.h"
#include <QSurfaceFormat>
#include <time.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
//    w.setFormat(format);
    w.show();
    return a.exec();
}
