varying vec3 v_V;
varying vec3 N;

void main()
{	
	N = gl_Normal;
	gl_TexCoord[0] = gl_MultiTexCoord0;

	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

	v_V = (gl_ModelViewMatrix * gl_Vertex).xyz;
}