#version 120

uniform sampler2D texture;
uniform vec3 lightpos;
uniform vec4 ambient;
uniform float shininess;

varying vec3 v_V;
varying vec3 v_P;

void main() {
	vec3 N = normalize(cross(dFdy(v_P), dFdx(v_P))); // N is the world normal
	vec3 V = normalize(v_V);
	vec3 R = reflect(V, N);
	vec3 L = normalize(lightpos);

	float diffuse = max(dot(L, N), 0.0);
	vec4 specular = gl_FrontMaterial.specular * pow(max(dot(R, L), 0.0), shininess);

	gl_FragColor = (ambient + diffuse + specular) * texture2D( texture, gl_TexCoord[0].st);
}