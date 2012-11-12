/*uniform sampler2D displacement;

varying vec3 v_V;
varying vec3 N;

void main()
{	
	N = gl_Normal;
	gl_TexCoord[0] = gl_MultiTexCoord0;

	vec4 dv = texture2D( displacement, gl_TexCoord[0].xy );
	float df = 0.30*dv.x + 0.59*dv.y + 0.11*dv.z;
	vec4 newVertexPos = vec4(N * df * 0.05, 0.0) + gl_Vertex;
	
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * newVertexPos;

	v_V = (gl_ModelViewMatrix * gl_Vertex).xyz;
}*/


uniform vec4 lightpos;
varying vec3 lightDir,normal;
varying vec3 v_V;

void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	v_V = (gl_ModelViewMatrix * gl_Vertex).xyz;
	
	lightDir = normalize((gl_ProjectionMatrix * gl_ModelViewMatrix * lightpos).xyz);
	normal = gl_Normal;

	gl_Position = ftransform();
} 
