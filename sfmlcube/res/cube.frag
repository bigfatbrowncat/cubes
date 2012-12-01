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
   float glossyA = 0.2;
   float glossyD = 0.02;

   float lighting = dot(vNormal, vView);
   
   float shade = dot(vLight1, vNormal);
   
   float gloss = 1.0 + glossyA * exp(-(lighting - 1.0) * (lighting - 1.0) / glossyD / glossyD);
   
   //lighting = 0.5 + round(lighting * 2) / 3;
   //lighting = 0.7 + 0.3 * lighting;
   
   gl_FragColor = 1.5 * ((ambient + shade) * diffuse) * /*gloss */ texture2D(texture, textureCoords);
   gl_FragColor.a = transparency; 
}   
