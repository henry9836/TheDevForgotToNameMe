#version 450 core

in vec3 fragColor;

out vec4 color;

uniform float currentTime;

void main(void){
    vec3 colorTemp = new vec3(((fragColor.x / abs(sin(currentTime)))+sin(currentTime)), (fragColor.y / abs(sin(currentTime))) , (fragColor.z));
    color = vec4(colorTemp, 1.0);
}