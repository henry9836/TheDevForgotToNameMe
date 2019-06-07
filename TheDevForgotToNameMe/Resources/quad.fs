#version 450 core

in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 color;

uniform float currentTime;
uniform sampler2D tex;
uniform sampler2D tex1;

void main(void){
    color = mix(texture(tex, fragTexCoord), texture(tex1, fragTexCoord), 1.0 * abs(sin(currentTime)));
}