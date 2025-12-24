#version 450

layout(location = 0) in vec2 position;

out vec3 vertex_color;

void main(void) {
	gl_Position = vec4(position, 0.0, 1.0);

	vec3 colors[3] = vec3[3](
		vec3(1.0, 0.0, 0.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 0.0, 1.0)
	);
	vertex_color = colors[gl_VertexID % 3];
}