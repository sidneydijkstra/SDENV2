#version 330 core
// layput's
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 textureCord;

// out's
out vec2 fragTextureCord;
out vec3 fragNormal;
out vec3 fragPosition;

// met4's
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
  // set gl position
    gl_Position = projection * view * model * vec4(position, 1.0f);

    // texture cordinates
    fragTextureCord = vec2(textureCord.x, 1.0 - textureCord.y);

    // texture normal
    fragNormal = mat3(transpose(inverse(model))) * normals;

    // this postition
    fragPosition = vec3(model * vec4(position, 1.0f));
}
