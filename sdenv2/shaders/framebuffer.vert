#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform float rotation; // 1 || -1
uniform float position; // -0.5f || 0.5f

void main()
{
    float x = aPos.x;
    float y = (aPos.y / 2) + position;

    vec2 newTCoord = aTexCoords;
    if(position == -0.5f){
      newTCoord.y = -aTexCoords.y;

      y -= 0.005f;
    }else{
      y += 0.005f;
    }
    TexCoords = vec2(newTCoord);

    gl_Position = vec4(x, y, 0, 1.01);
}
