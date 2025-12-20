#version 450

uniform vec2 apex;
uniform vec2 base1;
uniform vec2 base2;

void main(void) {
	vec2 positions[3] = vec2[3](apex, base1, base2);
	gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);
}