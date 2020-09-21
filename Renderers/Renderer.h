#ifndef RENDERER_H
#define RENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/types_c.h>

#include <Utilities/CGUtilities.h>
#include <Utilities/VertexBuffer.h>
#include <Utilities/Shader.h>
#include <Utilities/VertexArray.h>
#include <Logic/Tetris.h>


#include <vector>


class Renderer: public QOpenGLWidget, protected QOpenGLFunctions, public CGUtilities
{
    Q_OBJECT
public:
    Renderer(QWidget *parent = nullptr);
    void initializeGL() override;
    void initialize(Tetris* tetris);
    void resizeGL(int width, int height) override;
    void paintGL() override;
    void render();
private:

    Tetris* m_tetris;

    std::vector<uint> m_textureIDs;
    int m_samplers[TETROMINO_AMOUNT +1];


    void printContextInformation();

    inline GLuint LoadTexture(const std::string& path);

    VertexArray m_VAO;

    VertexBuffer m_VertexTexCoordsVBO;
    VertexBuffer m_displacementVBO;
    VertexBuffer m_tetrominoIndexVBO;


    Shader m_program;
    int m_verticesSize;

    glm::vec4 m_materialAmbientColor, m_materialDiffuseColor, m_materialSpecularColor;
    float     m_shineness;

    int m_thetaRes;
    int m_phiRes;

    bool m_initialized;
    bool m_attributesFlag;

};

#endif // RENDERER_H
