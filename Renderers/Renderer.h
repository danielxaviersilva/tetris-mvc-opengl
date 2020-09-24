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


class Renderer: public CGUtilities
{
public:
    Renderer();
    void initialize();
    void render(const std::vector<glm::vec2>& centerSet, std::vector<float>& tetrominoSet);
private:

    Tetris* m_tetris;
    bool m_initialized;

    std::vector<uint> m_textureIDs;
    int m_samplers[TETROMINO_AMOUNT +1];


    void printContextInformation();

    inline GLuint LoadTexture(const std::string& path);

    VertexArray m_VAO;
    VertexArray m_BkgVAO;
    VertexBuffer m_BkgVBO;

    VertexBuffer m_VertexTexCoordsVBO;
    VertexBuffer m_displacementVBO;
    VertexBuffer m_tetrominoIndexVBO;


    Shader m_program;

    const float m_BGSlot = 8.0f;
    int m_bkgTextureIndex;



};

#endif // RENDERER_H
