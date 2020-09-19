#version 400
#define BORDER 7 //0 to BORDER-1 is texture to tetromino, index BORDER is the Boundary Texture

in vec2 a_vertex;
in vec2 a_textureCoords;
in vec2 ia_displacement;
in float ia_tetrominoIndex;
uniform sampler 2D textureSet[BORDER+1];
uniform float u_fieldWidth;
uniform float u_fieldHeight;


out float o_tetrominoIndex;
out vec2 o_textureCoords;



void main(void) 
{
	o_tetrominoIndex = ia_tetrominoIndex;
	o_textureCoords = a_textureCoords;	
	gl_Position = (a_vertex*vec2(2/u_fieldWidth), 2/u_fieldHeight) + ia_displacement;
}

