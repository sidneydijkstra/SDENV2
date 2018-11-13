#version 330 core

// texture cords
in vec2 fragTextureCord;

// exit color
out vec4 exitColor;

// mesh color
uniform vec3 fragObjectColor;

// texture
uniform sampler2D ourTexture;
uniform bool doTexture;

void main(){
  if(doTexture){
    //genarate texture
    vec4 texture = texture(ourTexture, fragTextureCord);

    exitColor = vec4(texture.x, texture.y, texture.z, 1);
  }else{
    exitColor = vec4(fragObjectColor, 1);
  }
}
