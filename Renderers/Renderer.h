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
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#define BACKGROUND_INDEX 9 //If changed, go to shader to apply the same value so it matches


class Renderer: public CGUtilities
{
public:
    Renderer(bool centralizer = false);
    ~Renderer();
    void initialize(const int fieldWidth, const int fieldHeight);
    void render(const std::vector<float>& tetrominoSet);

private:

    bool m_initialized;

    std::vector<GLuint> m_textureIDs;
    int m_samplers[TETROMINO_AMOUNT+1];

    void printContextInformation();

    inline GLuint LoadTexture(const std::string& path);

    VertexArray m_VAO;
    VertexArray m_BkgVAO;
    VertexBuffer m_BkgVBO;

    VertexBuffer m_VertexTexCoordsVBO;
    VertexBuffer m_displacementVBO;
    VertexBuffer m_tetrominoIndexVBO;
    Shader m_program;

    GLuint m_bkgTextureIndex;

    std::vector<glm::vec2> m_centerSet;
    const bool m_centralizer;
    GLint m_activeTetrominosPositionMeanLocation;

    inline void setBlockVAOLayout();
    inline void setBackgroundVAOLayout();
    inline void setFixedBlockAttributes(int fieldWidth, int fieldHeight);
    inline void setBackgroundAttributes();
};

#endif // RENDERER_H
