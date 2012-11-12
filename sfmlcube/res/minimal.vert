varying vec3 lightDir;
varying vec3 V, N;

void main()
{	// Vertex position
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

	// Texture coords
	gl_TexCoord[0] = gl_MultiTexCoord0;

	// Direction to the light	
	lightDir = normalize((gl_ProjectionMatrix * gl_LightSource[0].position).xyz);
	// Vertex vector and normal
	V = normalize((gl_ModelViewMatrix * gl_Vertex).xyz);
	N = gl_Normal;
	
} 
