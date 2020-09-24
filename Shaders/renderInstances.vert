#version 400

#define TETROMINO_AMOUNT 7 //0 to TETROMINO_AMOUNT-1 is texture to tetromino, index TETROMINO_AMOUNT is the Boundary Texture

in vec2 a_vertex;
in vec2 a_textureCoords;
in vec2 ia_displacement;
in float ia_tetrominoIndex;


uniform sampler2D u_textureSet[TETROMINO_AMOUNT+2];
uniform float u_fieldWidth;
uniform float u_fieldHeight;

out float o_tetrominoIndex;
out vec2 o_textureCoords;



void main(void) 
{
	o_tetrominoIndex = ia_tetrominoIndex;
        o_textureCoords = a_textureCoords;
        if( ia_tetrominoIndex< TETROMINO_AMOUNT+1)
            gl_Position = vec4(a_vertex*vec2(1/u_fieldWidth, 1/u_fieldHeight) + ia_displacement, 0.0, 1.0);
        else
            gl_Position = vec4(a_vertex+ia_displacement, 0.0, 1.0);
}

