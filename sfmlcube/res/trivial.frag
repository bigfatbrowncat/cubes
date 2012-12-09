uniform sampler2D texture;
varying vec4 textureCoords;

void main()
{
	gl_FragColor = texture2D(texture, textureCoords.xy);
}
