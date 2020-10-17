#include "Renderer.h"
#include <iostream>

Renderer::Renderer(): m_initialized(false){}

Renderer::~Renderer()
{
    if (!m_textureIDs.empty())
        glDeleteTextures(m_textureIDs.size(), &m_textureIDs[0]);

    glDeleteTextures(1, &m_bkgTextureIndex);
}

void Renderer::initialize(int fieldWidth, int fieldHeight)
{
    if(!m_initialized)
    {
        m_initialized = true;
        m_program.loadProgram("./Shaders/renderInstances.vert","./Shaders/renderInstances.frag");

        m_VertexTexCoordsVBO.genBuffer();
        m_displacementVBO.genBuffer();
        m_tetrominoIndexVBO.genBuffer();
        m_BkgVBO.genBuffer();

         setBlockVAOLayout();
         setFixedBlockAttributes(fieldWidth, fieldHeight);

         setBackgroundVAOLayout();
         setBackgroundAttributes();

         //Setting up Textures
         for (int i= 0; i <= TETROMINO_AMOUNT; i++) //1 boundary[0] + 7 pieces [1:7]
             m_textureIDs.push_back(LoadTexture(std::string("./Textures/TEX" + std::to_string(i) + ".png")));

         for (int i = 0; i <= TETROMINO_AMOUNT; i++)
             glUniform1i(glGetUniformLocation( m_program.getProgramID(), std::string("u_textureSet[" + std::to_string(i) + "]").c_str()), i);


         m_bkgTextureIndex = LoadTexture(std::string("./Textures/background.jpg"));
         glUniform1i(glGetUniformLocation( m_program.getProgramID(), std::string("u_background").c_str()), BACKGROUND_INDEX);
    }
}


void Renderer::render(const std::vector<float>& tetrominoSet)
{
   if(!m_initialized){
       std::cerr << "Renderer::render: class not initialized" << std::endl;
       return;
    }

   m_program.useProgram();
   //Rendering Background
   m_BkgVAO.bind();
   glActiveTexture(GL_TEXTURE0 + BACKGROUND_INDEX);
   glBindTexture(GL_TEXTURE_2D, m_bkgTextureIndex);   
   glDrawArrays(GL_TRIANGLE_FAN, 0,4);


   //Rendering Tetrominos
   m_VAO.bind();
   m_tetrominoIndexVBO.updateBufferData(tetrominoSet.data(), tetrominoSet.size()*sizeof(float));
   for (int i = 0; i <=  TETROMINO_AMOUNT; i++){
           glActiveTexture(GL_TEXTURE0 + i);
           glBindTexture(GL_TEXTURE_2D, m_textureIDs[i]);
   }
   glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, tetrominoSet.size());
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

//   std::cout << image.type() << std::endl;

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image.cols, image.rows,0, GL_BGRA,GL_UNSIGNED_BYTE, image.ptr());
   _check_gl_error(__FILE__,__LINE__);
   glBindTexture(GL_TEXTURE_2D, 0);

   image.release();
   return textureID;
}

void Renderer::setBlockVAOLayout()
{
    int locVertex =glGetAttribLocation(m_program.getProgramID(),"a_vertex");
    int locTexCoords = glGetAttribLocation(m_program.getProgramID(),"a_textureCoords");
    int locDisplacement = glGetAttribLocation(m_program.getProgramID(),"ia_displacement");
    int locTetrominoIndex = glGetAttribLocation(m_program.getProgramID(),"ia_tetrominoIndex");

    if(locVertex == -1 ||locTexCoords == -1 || locDisplacement == -1 || locTetrominoIndex == -1)
        std::cerr << "Renderer::initialize: At least one of the input names couldn't be found" << std::endl;

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
}

inline void Renderer::setBackgroundVAOLayout()
{
    int locVertex = glGetAttribLocation(m_program.getProgramID(),"a_vertex");
    int locTexCoords = glGetAttribLocation(m_program.getProgramID(),"a_textureCoords");
    int locDisplacement = glGetAttribLocation(m_program.getProgramID(),"ia_displacement");
    int locTetrominoIndex = glGetAttribLocation(m_program.getProgramID(),"ia_tetrominoIndex");

    if(locVertex == -1 ||locTexCoords == -1 || locDisplacement == -1 || locTetrominoIndex == -1)
        std::cerr << "Renderer::initialize: At least one of the input names couldn't be found" << std::endl;

    m_BkgVAO.bind();
    m_BkgVAO.push<float>(locVertex, 2);
    m_BkgVAO.push<float>(locTexCoords, 2);
    m_BkgVAO.push<float>(locDisplacement, 2);
    m_BkgVAO.push<float>(locTetrominoIndex, 1);
    m_BkgVAO.addBuffer(m_BkgVBO);
}

void Renderer::setFixedBlockAttributes(int fieldWidth, int fieldHeight)
{
    //Format: (vertex.x, vertex.y, TexCoord.u, TexCoord.v)
    std::vector<float> squareVertexTexCoords = {-1.0f/fieldWidth,-1.0f/fieldHeight,  0.0f, 0.0f,
                                                 1.0f/fieldWidth,-1.0f/fieldHeight,  1.0f, 0.0f,
                                                 1.0f/fieldWidth, 1.0f/fieldHeight,  1.0f, 1.0f,
                                                -1.0f/fieldWidth, 1.0f/fieldHeight,  0.0f, 1.0f};

    m_VertexTexCoordsVBO.updateBufferData(squareVertexTexCoords.data(), squareVertexTexCoords.size()*sizeof(float));

    std::vector<float> borderMeshX;
    std::vector<float> borderMeshY;
    std::vector<glm::vec2> centerSet;

    for(float i = -1; i <= 1.01; i+=(2/float(fieldWidth)))
        borderMeshX.push_back(i);

    for(float j = 1; j >= -1.01; j-=2/float(fieldHeight))
        borderMeshY.push_back(j);


    for(int j = 0; j < fieldHeight; j++)
        for(int i = 0; i < fieldWidth; i++)
            centerSet.push_back(glm::vec2(0.5f*(borderMeshX[i] + borderMeshX[i+1]), 0.5f*(borderMeshY[j] + borderMeshY[j+1])));
     m_displacementVBO.updateBufferData(centerSet.data(), centerSet.size()*sizeof(glm::vec2));
}

inline void Renderer::setBackgroundAttributes()
{
    std::vector<float> bkgAttributes = {-1.0f,-1.0f,  0.0f, 0.0f,0.0f,0.0f, BACKGROUND_INDEX,
                                         1.0f,-1.0f,  1.0f, 0.0f,0.0f,0.0f, BACKGROUND_INDEX,
                                         1.0f, 1.0f,  1.0f, 1.0f,0.0f,0.0f, BACKGROUND_INDEX,
                                        -1.0f, 1.0f,  0.0f, 1.0f,0.0f,0.0f, BACKGROUND_INDEX
                                       };
     m_BkgVBO.updateBufferData(bkgAttributes.data(), bkgAttributes.size()*sizeof(float));
}
