uniform sampler2D texture;
uniform vec4 color;

varying vec3  vNormal;
varying vec3  vLight1;

varying vec3  vView;
varying vec2  textureCoords;

void main(void)
{
   float glossyA = 10;
   float glossyD = 0.02;
   vec4 ambient = color; 
   vec4 diffuse = 0.6;

   float shade = dot(vNormal, vView);
   
   float lighting = dot(vLight1, vNormal);
   
   float gloss = 1 + glossyA * exp(-(lighting - 1) * (lighting - 1) / glossyD / glossyD);
   
   //lighting = 0.5 + round(lighting * 2) / 3;
   //lighting = 0.7 + 0.3 * lighting;
   
   gl_FragColor = (ambient + lighting * diffuse) * gloss * (texture2D(texture, textureCoords));
   gl_FragColor.a = 1; 
}   
