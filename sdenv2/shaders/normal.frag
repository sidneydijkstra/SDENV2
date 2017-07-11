#version 330 core
// in's
in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTextureCord;

// exit color
out vec4 exitColor;

// texture
uniform sampler2D ourTexture;

// vec3's
uniform vec3 fragObjectColor;
uniform vec3 fragLightColor;
uniform vec3 fragLightPosition;
uniform vec3 fragViewPosition;

uniform float fragAmbientStrength;
uniform float fragSpecularStrength;

void main(){

    // genarate texture
    vec4 mytexture = texture(ourTexture, fragTextureCord);

    // normalize normals
    vec3 norm = normalize(fragNormal);

    // ambient
    float ambientStrength = fragAmbientStrength;
    vec3 ambient = ambientStrength * fragLightColor;

    // diffuse
    vec3 lightDir = normalize(fragLightPosition - fragPosition);
    float diff = max(dot(lightDir, norm), 0.0f);
    vec3 diffuse = diff * fragLightColor;

    // specular
    float specularStrength = fragSpecularStrength;
    vec3 viewDir = normalize(fragViewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * fragLightColor;

    // calculate result
    vec3 result = (ambient + diffuse + specular);

    float gamma = 1.7;
    result.rgb = pow(result.rgb, vec3(1.0/gamma));
    // set exit color
    exitColor = vec4(result * mytexture.rgb, mytexture.a);
    //exitColor = vec4(result * vec3(1.2,0.2,2.3), 1);
}
