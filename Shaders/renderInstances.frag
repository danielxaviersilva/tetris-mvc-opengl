#version 400
#define TETROMINO_AMOUNT 7 //0 to TETROMINO_AMOUNT-1 is texture to tetromino, index TETROMINO_AMOUNT is the Boundary Texture


in float o_tetrominoIndex;
in vec2 o_textureCoords;
uniform sampler2D u_textureSet[TETROMINO_AMOUNT+2];
out vec4 fragColor;

void main (void) 
{
	fragColor = texture(u_textureSet[int(o_tetrominoIndex)], o_textureCoords);	
}	