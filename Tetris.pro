QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controllers/controller.cpp \
    Logic/Tetris.cpp \
    Renderers/Renderer.cpp \
    Utilities/CGUtilities.cpp \
    Utilities/IndexBuffer.cpp \
    Utilities/Texture.cpp \
    Utilities/Timer.cpp \
    Utilities/VertexArray.cpp \
    Utilities/VertexBuffer.cpp \
    Utilities/camera.cpp \
    Utilities/shader.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Controllers/controller.h \
    Logic/Tetris.h \
    MainWindow.h \
    Renderers/Renderer.h \
    Utilities/CGUtilities.h \
    Utilities/Camera.h \
    Utilities/IndexBuffer.h \
    Utilities/Shader.h \
    Utilities/Texture.h \
    Utilities/Timer.h \
    Utilities/VertexArray.h \
    Utilities/VertexBuffer.h \
    Utilities/renderCrossLine.h

INCLUDEPATH += "/usr/local/Cellar/glm/0.9.9.5/include" \
                "/usr/local/Cellar/glew/2.1.0_1/include/"

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv4

DISTFILES += \
    Shaders/renderInstances.frag \
    Shaders/renderInstances.vert
