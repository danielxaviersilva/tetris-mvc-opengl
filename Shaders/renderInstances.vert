#version 400

/*
u_textureSet indexing: 
*/



#define TETROMINO_AMOUNT 7 //0 to TETROMINO_AMOUNT-1 is texture to tetromino, index TETROMINO_AMOUNT is the Boundary Texture
#define BACKGROUND_INDEX 9

in vec2 a_vertex;
in vec2 a_textureCoords;
in vec2 ia_displacement;
in float ia_tetrominoIndex;

uniform vec2 u_activeTetrominosPositionMean;


//uniform sampler2D u_textureSet[TETROMINO_AMOUNT+1];

out float o_tetrominoIndex;
out vec2 o_textureCoords;
out vec2 o_normal;
out vec2 o_vertex;


void main(void) 
{
    o_tetrominoIndex = ia_tetrominoIndex;
    o_textureCoords = a_textureCoords;
    o_vertex = a_vertex + ia_displacement;
    o_normal = a_vertex;

    gl_Position = vec4(a_vertex + ia_displacement - u_activeTetrominosPositionMean, 0.0, 1.0);


}

