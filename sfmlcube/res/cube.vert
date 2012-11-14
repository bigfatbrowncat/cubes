uniform vec4 view_position;
uniform vec4 light0;

varying vec3  vNormal;
varying vec3  vView;

varying vec3  vLight1;

varying vec2 textureCoords;

void main(void)
{
   // Output transformed vertex position: 
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

   textureCoords = gl_MultiTexCoord0.st;
   vNormal = normalize(gl_NormalMatrix * gl_Normal);
   vLight1 = normalize(light0.xyz - gl_Vertex.xyz);
   vView = normalize(vec3(0, 0, 1000) - gl_Vertex.xyz);
   
}