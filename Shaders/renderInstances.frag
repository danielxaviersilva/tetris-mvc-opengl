#version 400
#define TETROMINO_AMOUNT 7 //0 to TETROMINO_AMOUNT-1 is texture to tetromino, index TETROMINO_AMOUNT is the Boundary Texture
#define BACKGROUND_INDEX 9


in float o_tetrominoIndex;
in vec2 o_textureCoords;
uniform sampler2D u_textureSet[TETROMINO_AMOUNT+2];
uniform sampler2D u_background;
out vec4 fragColor;

void main (void)
{
	int tetroIndex = int(o_tetrominoIndex);
	
	if (tetroIndex >= 1 && tetroIndex < BACKGROUND_INDEX)
		fragColor = texture(u_textureSet[tetroIndex-1], o_textureCoords);
	else if (tetroIndex == BACKGROUND_INDEX)
		fragColor = texture(u_background, o_textureCoords);
	else if(tetroIndex == 0)
		discard;

}	
