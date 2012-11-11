varying vec3 v_V;
varying vec3 v_P;

void main()
{	
	gl_TexCoord[0] = gl_MultiTexCoord0;

	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

	v_P = gl_Position.xyz; // v_P is the world position
	v_V = (gl_ModelViewMatrix * gl_Vertex).xyz;
}