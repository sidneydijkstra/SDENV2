#version 330 core

// layput's
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 textureCord;

// met4's
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    // set gl position
    gl_Position = projection * model * vec4(position, 1.0f);
}
