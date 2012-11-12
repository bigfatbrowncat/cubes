#version 120

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