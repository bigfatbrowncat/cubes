/*#version 120

uniform sampler2D texture;

uniform vec4 lightpos;
uniform vec4 specular;
uniform vec4 ambient;
uniform float shininess;

varying vec3 v_V;
varying vec3 N;

void main() {
	vec3 V = normalize(v_V);
	vec3 R = reflect(V, N);
	
	vec3 L = normalize((gl_ProjectionMatrix * gl_ModelViewMatrix * lightpos).xyz);

	float diffuse = max(dot(L, N), 0.0);
	vec4 spec = specular * pow(max(dot(R, L), 0.0), shininess);

	gl_FragColor = (ambient + diffuse + spec) * texture2D( texture, gl_TexCoord[0].st);
}
*/

uniform sampler2D texture;
varying vec3 lightDir;
varying vec3 V, N;

void main()
{
	vec4 ambient = vec4(0.2, 0.2, 0.2, 1);
	vec4 diffuse = vec4(0.8, 0.8, 0.8, 1);

	float intensity;
	vec4 color;
	
	// normalizing the lights position to be on the safe side
	
	//intensity = dot(lightDir, N);												// clay
	intensity = abs(3 * pow(dot(lightDir, N), 3) - 0.3 * length(cross(V, N)));		// glance metal
	//intensity = 0.2 * pow(4 * pow(dot(lightDir, N), 3) + 0.5 * pow(length(cross(V, N)), 3), 2);		// matte metal

	//int toonShaderK = 2;
	//intensity = round(toonShaderK * intensity) / toonShaderK;	// for toon shading
	
	
	color = texture2D( texture, gl_TexCoord[0].st) * (ambient + diffuse * intensity);
	color.r = clamp(color.r, 0, 1);
	color.g = clamp(color.g, 0, 1);
	color.b = clamp(color.b, 0, 1);

	
	gl_FragColor = color;
} 
