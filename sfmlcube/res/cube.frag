uniform sampler2D texture;
uniform vec4 ambient;
uniform vec4 diffuse;
uniform float transparency;

varying vec3  vNormal;
varying vec3  vLight1;

varying vec3  vView;
varying vec2  textureCoords;

void main(void)
{
   float shade = dot(vLight1, vNormal);
   
   gl_FragColor = 1.5 * ((ambient + shade) * diffuse) * texture2D(texture, textureCoords);
   gl_FragColor.a = transparency; 
}   
