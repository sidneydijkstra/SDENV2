#version 330 core
// layput's
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCord;

// texture cords
out vec2 fragTextureCord;

// met4's
uniform mat4 MVP;

void main(){
    // set gl position
    gl_Position = MVP * vec4(vec3(position.x, position.y, 0), 1.0f);

    // texture cordinates
    fragTextureCord = vec2(textureCord.x, 1.0 - textureCord.y);
}
