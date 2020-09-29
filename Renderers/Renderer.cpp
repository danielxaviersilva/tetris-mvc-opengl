#include "Renderer.h"
#include <iostream>
#include <chrono>

Renderer::Renderer(): m_initialized(false)
{
}

void Renderer::initialize()
{
    if(!m_initialized)
    {
        m_initialized = true;
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

         m_BkgVBO.genBuffer();

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


         for (int i= 0; i <= TETROMINO_AMOUNT; i++) //7 to pieces + 1 boundary
             m_textureIDs.push_back(LoadTexture(std::string("/Users/daniel_mac/Projetos/Tetris/Textures/TEX" + std::to_string(i) + ".png")));

         for (int i = 0; i <= TETROMINO_AMOUNT; i++)
             m_samplers[i] = i;

         for (int i = 0; i <= TETROMINO_AMOUNT; i++)
             glUniform1i(glGetUniformLocation( m_program.getProgramID(), std::string("u_textureSet[" + std::to_string(i) + "]").c_str()), i);



         m_BkgVAO.bind();
         m_BkgVAO.push<float>(locVertex, 2);
         m_BkgVAO.push<float>(locTexCoords, 2);
         m_BkgVAO.push<float>(locDisplacement, 2);
         m_BkgVAO.push<float>(locTetrominoIndex, 1);
         m_BkgVAO.addBuffer(m_BkgVBO);

         std::vector<float> bkgAttributes = {-1.0f,-1.0f,  0.0f, 0.0f,0.0f,0.0f, m_BGSlot,
                                              1.0f,-1.0f,  1.0f, 0.0f,0.0f,0.0f, m_BGSlot,
                                              1.0f, 1.0f,  1.0f, 1.0f,0.0f,0.0f, m_BGSlot,
                                             -1.0f, 1.0f,  0.0f, 1.0f,0.0f,0.0f, m_BGSlot
                                            };
          m_BkgVBO.updateBufferData(bkgAttributes.data(), bkgAttributes.size()*sizeof(float));
          _check_gl_error(__FUNCTION__,__LINE__);

          m_bkgTextureIndex = LoadTexture(std::string("/Users/daniel_mac/Projetos/Tetris/Textures/background.jpg"));
          _check_gl_error(__FUNCTION__,__LINE__);
          glUniform1i(glGetUniformLocation( m_program.getProgramID(), std::string("u_textureSet[8]").c_str()), 8);
          _check_gl_error(__FUNCTION__,__LINE__);


    }
     _check_gl_error(__FILE__,__LINE__);


}


void Renderer::render(const std::vector<glm::vec2>& centerSet, std::vector<float>& tetrominoSet)
{

    std::cout <<"paint" << std::endl;
   if(!m_initialized)
       return;
   std::cout <<"paintRender" << std::endl;

//   glClearColor(1.0f,1.0f,1.0f,1.0f);
   m_program.useProgram();
   glActiveTexture(GL_TEXTURE8 /*+ int(m_BGSlot)*/);
   _check_gl_error(__FUNCTION__,__LINE__);
   glBindTexture(GL_TEXTURE_2D,m_bkgTextureIndex);
   _check_gl_error(__FUNCTION__,__LINE__);

   m_BkgVAO.bind();

   glDrawArrays(GL_TRIANGLE_FAN, 0,4);



   m_VAO.bind();


   for (int i = 0; i <=  TETROMINO_AMOUNT; i++){
//    int i = 0;
           glActiveTexture(GL_TEXTURE0 + i);
           glBindTexture(GL_TEXTURE_2D, m_textureIDs[i]);

   }

   m_displacementVBO.updateBufferData(centerSet.data(), centerSet.size()*sizeof(glm::vec2));
   _check_gl_error(__FILE__,__LINE__);
   m_tetrominoIndexVBO.updateBufferData(tetrominoSet.data(), tetrominoSet.size()*sizeof(float));
   _check_gl_error(__FILE__,__LINE__);

   glDisable(GL_CULL_FACE);

   glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, tetrominoSet.size());
   _check_gl_error(__FILE__,__LINE__);

}

inline GLuint Renderer::LoadTexture(const std::string &path)
{
    cv::Mat image = cv::imread(path.c_str(), -1);
        if(image.empty()){
              std::cerr << "Texture::Texture(): Texture not load. Path is invalid." << std::endl;
              return 0;
        }
        cv::cvtColor(image, image, cv::COLOR_RGB2RGBA);
//    cv::flip(image, image, 0);
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
   glBindTexture(GL_TEXTURE_2D, 0);

   image.release();
   return textureID;


}
