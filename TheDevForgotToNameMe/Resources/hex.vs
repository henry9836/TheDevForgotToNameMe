#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 fragColor;

uniform float currentTime;

void main(void){
	float s = (sin(currentTime/-0.5))/1.5;
	float c = (cos(currentTime/-0.5))/1.5;
	mat2 rot = mat2(c, s, -s, c);
	vec2 pos = rot * position.xy;
	gl_Position = vec4(pos, position.z, 1);
	fragColor = color;
}
