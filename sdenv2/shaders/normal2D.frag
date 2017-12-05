#version 330 core

// exit color
out vec4 exitColor;

// mesh color
uniform vec3 fragObjectColor;

void main(){
  exitColor = vec4(fragObjectColor, 1.0);
}
