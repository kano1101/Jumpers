#version 400

uniform vec4 uColor;

// in vec3 fragmentColor;
out vec4 color;
void main() {
	// color = vec3(1.0f, 0.5f, 0.2f);
	color = uColor;
	// color = vec3(fragmentColor[0],fragmentColor[1],fragmentColor[2]);
}
