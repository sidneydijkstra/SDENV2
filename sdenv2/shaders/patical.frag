#version 330 core
// in's
in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTextureCord;

// exit color
out vec4 exitColor;

// texture
uniform sampler2D ourTexture;

void main(){
  exitColor = vec4(1,1,1,1);
}
