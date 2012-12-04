uniform sampler2D texture;
varying vec2 textureCoords;

void main()
{
	gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex;
	textureCoords  = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}
