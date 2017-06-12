/*
#version 330 core

in vec2 fragTextureCoord;
in vec3 fragPosition;

out vec4 color;

// textures
uniform sampler2D fragTexture;

void main(){
  vec4 textureColor = texture2D(fragTexture, fragTextureCoord);
  color = vec4(textureColor.rgb, textureColor.a);
}
*/
#version 330 core

in vec2 FragTextureCord;

out vec4 exitColor;

uniform sampler2D ourTexture;

void main()
{
    exitColor = texture(ourTexture, FragTextureCord);
}
