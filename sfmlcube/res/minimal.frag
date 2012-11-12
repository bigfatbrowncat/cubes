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

varying vec3 lightDir,normal;
uniform sampler2D texture;
varying vec3 v_V;

void main()
{
	vec3 V = normalize(v_V);

	float intensity;
	vec4 color;
	
	// normalizing the lights position to be on the safe side
	
	vec3 n = normalize(normal);
	
	intensity = dot(lightDir,n);													// clay
	//intensity = abs(3 * pow(dot(lightDir,n), 3) - pow(length(cross(V,n)), 0.6));	// metal
	
	//intensity = round(5 * intensity) / 5;	// for toon shading
	
	color = texture2D( texture, gl_TexCoord[0].st) * (0.2 + 0.8 * intensity);
	
	gl_FragColor = color;
} 
