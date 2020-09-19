#version 400
#define BORDER 7 //0 to BORDER-1 is texture to tetromino, index BORDER is the Boundary Texture


in float o_tetrominoIndex;
in vec2 o_textureCoords;
uniform sampler 2D textureSet[BORDER+1];
out vec4 fragColor;

void main (void) 
{
	fragColor = texture(textureSet[int(o_tetrominoIndex)], o_textureCoords);	
}