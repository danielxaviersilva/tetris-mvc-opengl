#include "Renderer.h"
#include <iostream>
#include <chrono>

Renderer::Renderer(QWidget *parent): QOpenGLWidget{parent}, m_initialized(false)
{
    QSurfaceFormat format;
    format.setVersion(4,1);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
    this->setFormat(format);

}

void Renderer::initializeGL()
{

    initializeOpenGLFunctions();
    glClearColor(1,1,1,1);
//    PrintProfile(format); // Prints out the QSurfaceFormat::OpenGLContextProfile
//    printContextInformation();

//            m_tetris = tetris;
            m_program.loadProgram("/Users/daniel_mac/Projetos/Tetris/Shaders/renderInstances.vert","/Users/daniel_mac/Projetos/Tetris/Shaders/renderInstances.frag");
             int locVertex =glGetAttribLocation(m_program.getProgramID(),"a_vertex");
             int locTexCoords = glGetAttribLocation(m_program.getProgramID(),"a_textureCoords");
             int locDisplacement = glGetAttribLocation(m_program.getProgramID(),"ia_displacement");
             int locTetrominoIndex = glGetAttribLocation(m_program.getProgramID(),"ia_tetrominoIndex");

             if(locVertex == -1 ||locTexCoords == -1 || locDisplacement == -1 || locTetrominoIndex == -1)
                 std::cerr << "Renderer::initialize: At least one of the input names couldn't be found" << std::endl;

             m_VertexTexCoordsVBO.genBuffer();
             m_displacementVBO.genBuffer();
             m_tetrominoIndexVBO.genBuffer();






             m_VAO.bind();
             m_VAO.push<float>(locVertex, 2);
             m_VAO.push<float>(locTexCoords, 2);
             m_VAO.addBuffer(m_VertexTexCoordsVBO);
             m_VAO.clearLayout();

             m_VAO.push<float>(locDisplacement, 2,GL_FALSE, VertexArray::INSTANTIATION_MODE::INSTANCED, 1);
             m_VAO.addBuffer(m_displacementVBO);
             m_VAO.clearLayout();

             m_VAO.push<float>(locTetrominoIndex,1, GL_FALSE, VertexArray::INSTANTIATION_MODE::INSTANCED, 1);
             m_VAO.addBuffer(m_tetrominoIndexVBO);
             m_VAO.clearLayout();


             //Format: (vertex.x, vertex.y, TexCoord.u, TexCoord.v)
             std::vector<float> squareVertexTexCoords = {-1.0f,-1.0f,  0.0f, 0.0f,
                                                          1.0f,-1.0f,  1.0f, 0.0f,
                                                          1.0f, 1.0f,  1.0f, 1.0f,
                                                         -1.0f, 1.0f,  0.0f, 1.0f};
             m_VertexTexCoordsVBO.updateBufferData(squareVertexTexCoords.data(), squareVertexTexCoords.size()*sizeof(float));


             float width = m_tetris->getFieldWidth();
             glUniform1f (m_program.getUniformLocation("u_fieldWidth"),width );

             float height = m_tetris->getFieldHeight();
             glUniform1f (m_program.getUniformLocation("u_fieldHeight"),height);



//             int texLoc = glGetUniformLocation(m_program.getProgramID(), "u_textureSet");

             for (int i= 0; i <= TETROMINO_AMOUNT; i++) //7 to pieces + 1 boundary
                 m_textureIDs.push_back(LoadTexture(std::string("/Users/daniel_mac/Projetos/Tetris/Textures/TEX" + std::to_string(i) + ".png")));

             for (int i = 0; i <= TETROMINO_AMOUNT; i++)
                 m_samplers[i] = i;

             for (int i = 0; i <= TETROMINO_AMOUNT; i++) {
                 auto temp = glGetUniformLocation( m_program.getProgramID(), std::string("u_textureSet[" + std::to_string(i) + "]").c_str());

                 glUniform1i(glGetUniformLocation( m_program.getProgramID(), std::string("u_textureSet[" + std::to_string(i) + "]").c_str()), i);
             }

//             glUniform1iv(texLoc, TETROMINO_AMOUNT+1, m_samplers);
             _check_gl_error(__FILE__,__LINE__);


    std::cout <<"initializeGL" << std::endl;


}

void Renderer::initialize(Tetris* tetris)
{
//    initializeOpenGLFunctions();
//    glClearColor(1,1,1,1);
////    PrintProfile(format); // Prints out the QSurfaceFormat::OpenGLContextProfile
////    printContextInformation();
    if(!m_initialized)
        {

            m_initialized = true;
            m_tetris = tetris;
//            m_program.loadProgram("/Users/daniel_mac/Projetos/Tetris/Shaders/renderInstances.vert","/Users/daniel_mac/Projetos/Tetris/Shaders/renderInstances.frag");
//             int locVertex =glGetAttribLocation(m_program.getProgramID(),"a_vertex");
//             int locTexCoords = glGetAttribLocation(m_program.getProgramID(),"a_textureCoords");
//             int locDisplacement = glGetAttribLocation(m_program.getProgramID(),"ia_displacement");
//             int locTetrominoIndex = glGetAttribLocation(m_program.getProgramID(),"ia_tetrominoIndex");

//             if(locVertex == -1 ||locTexCoords == -1 || locDisplacement == -1 || locTetrominoIndex == -1)
//                 std::cerr << "Renderer::initialize: At least one of the input names couldn't be found" << std::endl;

//             m_VertexTexCoordsVBO.genBuffer();
//             m_displacementVBO.genBuffer();
//             m_tetrominoIndexVBO.genBuffer();






//             m_VAO.bind();
//             m_VAO.push<float>(locVertex, 2);
//             m_VAO.push<float>(locTexCoords, 2);
//             m_VAO.addBuffer(m_VertexTexCoordsVBO);
//             m_VAO.clearLayout();

//             m_VAO.push<float>(locDisplacement, 2,GL_FALSE, VertexArray::INSTANTIATION_MODE::INSTANCED, 1);
//             m_VAO.addBuffer(m_displacementVBO);
//             m_VAO.clearLayout();

//             m_VAO.push<float>(locTetrominoIndex,1, GL_FALSE, VertexArray::INSTANTIATION_MODE::INSTANCED, 1);
//             m_VAO.addBuffer(m_tetrominoIndexVBO);
//             m_VAO.clearLayout();


//             //Format: (vertex.x, vertex.y, TexCoord.u, TexCoord.v)
//             std::vector<float> squareVertexTexCoords = {-1.0f,-1.0f,  0.0f, 0.0f,
//                                                          1.0f,-1.0f,  1.0f, 0.0f,
//                                                          1.0f, 1.0f,  1.0f, 1.0f,
//                                                         -1.0f, 1.0f,  0.0f, 1.0f};
//             m_VertexTexCoordsVBO.updateBufferData(squareVertexTexCoords.data(), squareVertexTexCoords.size()*sizeof(float));


//             float width = m_tetris->getFieldWidth();
//             glUniform1f (m_program.getUniformLocation("u_fieldWidth"),width );

//             float height = m_tetris->getFieldHeight();
//             glUniform1f (m_program.getUniformLocation("u_fieldHeight"),height);



//             int texLoc = glGetUniformLocation(m_program.getProgramID(), "u_textureSet");

//             for (int i= 0; i <= TETROMINO_AMOUNT; i++) //7 to pieces + 1 boundary
//                 m_textureIDs.push_back(LoadTexture(std::string("/Users/daniel_mac/Projetos/Tetris/Textures/TEX" + std::to_string(i) + ".png")));

//             for (int i = 0; i <= TETROMINO_AMOUNT; i++)
//                 m_samplers[i] = i;

//             glUniform1iv(texLoc, TETROMINO_AMOUNT+1, m_samplers);
//             _check_gl_error(__FILE__,__LINE__);

    }

     std::cout <<"initialize" << std::endl;


}

void Renderer::resizeGL(int width, int height)
{


}

void Renderer::paintGL()
{
     std::cout <<"paint" << std::endl;
    if(!m_initialized)
        return;
    std::cout <<"paintRender" << std::endl;

    glClearColor(1,1,1,1);
    m_program.useProgram();
    m_VAO.bind();
    _check_gl_error(__FUNCTION__,__LINE__);

    for (int i = 0; i <=  TETROMINO_AMOUNT; i++){
//    int i = 0;
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, m_textureIDs[i]);

//        glBindTextureUnit(m_samplers[i], m_textureIDs[i]);
    }
    _check_gl_error(__FILE__,__LINE__);

    std::vector<glm::vec2> centerSet = m_tetris->getCurrentCenters();
    std::vector<float> tetrominoSet = m_tetris->getTetrominoIndex();
    _check_gl_error(__FILE__,__LINE__);

    m_displacementVBO.updateBufferData(centerSet.data(), centerSet.size()*sizeof(glm::vec2));
    _check_gl_error(__FILE__,__LINE__);
    m_tetrominoIndexVBO.updateBufferData(tetrominoSet.data(), tetrominoSet.size()*sizeof(float));
    _check_gl_error(__FILE__,__LINE__);

    glDisable(GL_CULL_FACE);

    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, tetrominoSet.size());
    _check_gl_error(__FILE__,__LINE__);
    update();


//   update();

}

void Renderer::render()
{
//    glClearColor(1,1,1,1);
//    m_program.useProgram();
//    m_VAO.bind();
//    _check_gl_error(__FUNCTION__,__LINE__);

//    for (int i = 0; i <=  TETROMINO_AMOUNT; i++){
//            glActiveTexture(GL_TEXTURE0 + i);
//            glBindTexture(GL_TEXTURE_2D, m_textureIDs[i]);
//    }
////        glBindTextureUnit(m_samplers[i], m_textureIDs[i]);
//    _check_gl_error(__FILE__,__LINE__);

//    std::vector<glm::vec2> centerSet = m_tetris->getCurrentCenters();
//    std::vector<float> tetrominoSet = m_tetris->getTetrominoIndex();
//    _check_gl_error(__FILE__,__LINE__);

//    m_displacementVBO.updateBufferData(centerSet.data(), centerSet.size()*sizeof(glm::vec2));
//    _check_gl_error(__FILE__,__LINE__);
//    m_tetrominoIndexVBO.updateBufferData(tetrominoSet.data(), tetrominoSet.size()*sizeof(float));
//    _check_gl_error(__FILE__,__LINE__);

//    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, tetrominoSet.size());
//    _check_gl_error(__FILE__,__LINE__);
//    update();
////    sleep_for()


}


void Renderer::printContextInformation()
{
  QString glType;
  QString glVersion;
  QString glProfile;

  // Get Version Information
  glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
  glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

//  std::cout << glVersion.toStdString()  << std::endl;
  // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
  switch (format().profile())
  {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
  }
#undef CASE

//   qPrintable() will print our QString w/o quotes around it.
  std::cout << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")" << std::endl;
}

inline GLuint Renderer::LoadTexture(const std::string &path)
{
    cv::Mat image = cv::imread(path.c_str(), -1);
        if(image.empty()){
              std::cerr << "Texture::Texture(): Texture not load. Path is invalid." << std::endl;
              return 0;
        }
    cv::flip(image, image, 0);
//        cv::imshow(path, image);

   GLuint textureID;
   glGenTextures(1, &textureID);
   glBindTexture(GL_TEXTURE_2D, textureID);

   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

   std::cout << image.type() << std::endl;

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image.cols, image.rows,0, GL_BGRA,GL_UNSIGNED_BYTE, image.ptr());
   _check_gl_error(__FILE__,__LINE__);
//   glBindTexture(GL_TEXTURE_2D, 0);

   image.release();
   return textureID;


}
