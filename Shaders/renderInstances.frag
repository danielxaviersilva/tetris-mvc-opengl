#version 400
#define TETROMINO_AMOUNT 7 //0 to TETROMINO_AMOUNT-1 is texture to tetromino, index TETROMINO_AMOUNT is the Boundary Texture
#define BACKGROUND_INDEX 9


in float o_tetrominoIndex;
in vec2 o_normal;
in vec2 o_textureCoords;
in vec2 o_vertex;
uniform sampler2D u_textureSet[TETROMINO_AMOUNT+2];
uniform sampler2D u_background;
out vec4 fragColor;

void setDiffuseLight(in vec3 materialDiffuseColor, in vec3 sourceDiffuseColor,
                                     in vec3 lightLocation, in vec3 normal, in vec3 vertice,
                                     out vec3 resultDiffuseColor);



void main (void)
{
	int tetroIndex = int(o_tetrominoIndex);
        vec3 diffuseLight;


	
        if (tetroIndex >= 1 && tetroIndex < BACKGROUND_INDEX){
                vec4 textureValue = texture(u_textureSet[tetroIndex-1], o_textureCoords);
                setDiffuseLight(vec3(textureValue), vec3(1.0), vec3(-1.0, 1.0, 0.0), vec3(o_normal, 0.0), vec3(o_vertex, 0.0), diffuseLight);
                fragColor = vec4(0.6*vec3(textureValue) + 0.4*diffuseLight, 1.0);
        }
	else if (tetroIndex == BACKGROUND_INDEX)
		fragColor = texture(u_background, o_textureCoords);
	else if(tetroIndex == 0)
		discard;
}	




void setDiffuseLight(in vec3 materialDiffuseColor, in vec3 sourceDiffuseColor,
                                     in vec3 lightLocation, in vec3 normal, in vec3 vertice,
                                     out vec3 resultDiffuseColor)
{
    vec3 lightDirection = normalize(lightLocation - vertice);
    if(dot(normalize(lightDirection), normalize(normal)) > 0.0)
        resultDiffuseColor = dot(normalize(lightDirection), normalize(normal))*materialDiffuseColor*sourceDiffuseColor;
    else
        resultDiffuseColor = vec3(0.0);
}
