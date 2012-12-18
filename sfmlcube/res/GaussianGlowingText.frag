uniform sampler2D texture;
varying vec4 textureCoords;

uniform float blur_radius;
uniform vec2 blur_vector;

uniform vec4 glowing_color;
uniform float glowing_pressure;

uniform float screen_width;
uniform float screen_height;

void main()
{
	vec2 delta = vec2(blur_vector.x / screen_width, blur_vector.y / screen_height);
	
	vec4 pixel = vec4(0.0, 0.0, 0.0, 0.0);
	float d = 0.0;
	float ddmin = 1.0 / (-(abs(blur_radius + 1.0) + 1.0) / blur_radius * 2.0);
	for (float j = -blur_radius; j <= blur_radius; j++)
	{
		float dd = 1.0 / (-(abs(j) + 1) / blur_radius * 2.0) - ddmin;
		pixel += texture2D(texture, textureCoords.xy + delta * j) * dd;
		d += dd;
	}
	
	pixel = pixel / d * glowing_pressure;
	gl_FragColor = vec4(glowing_color.x, glowing_color.y, glowing_color.z, glowing_color.a * pixel.a);
}
