#version 330 core

in vec2 fragTextureCoord;
in vec3 fragNormal;
in vec3 fragPosition;

out vec4 color;

// textures
uniform sampler2D fragTexture;
uniform sampler2D fragNormalMap;

// vector3
uniform vec3 fragObjectColor;
uniform vec3 fragLightColor;
uniform vec3 fragLightPosition;
uniform vec3 fragViewPosition;

// booleans
uniform bool doLighting;
uniform bool doTexture;
uniform bool doNormalMap;

void main(){
  // temp textureColor variabel
  vec4 textureColor;

  // if there is a texture add it to textureColor
  if(doTexture){
    // create texture
    textureColor = texture2D(fragTexture, fragTextureCoord);
  }

  // test if there is a light in the current scene
  if(doLighting){

    // temp norm variabel
    vec3 norm;
    // get normal map texture color
    vec3 normalMap = texture(fragNormalMap, fragTextureCoord).rgb;

    // if there is a normalTexture add it to normalMap
    if(doNormalMap){
      // proces normal map
      norm = (normalize(normalMap * 2.0 - 1.0)) * 1.0f;
    }else{
      norm = normalize(fragNormal);
    }

    // ambient
    float ambientStrength = 0.15f;
    vec3 ambient = ambientStrength * fragLightColor;

    // diffuse
    vec3 lightDir = normalize(fragLightPosition - fragPosition);
    float diff = max(dot(lightDir, norm), 0.0f);
    vec3 diffuse = diff * fragLightColor;

    // specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(fragViewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * fragLightColor;

    // temp result variable
    vec3 result;

    // if there is a object color use it in result
    if(fragObjectColor == vec3(0.0f, 0.0f, 0.0f)){
      result = (ambient + diffuse + specular);
    }else{
      result = (ambient + diffuse + specular) * fragObjectColor;
    }

    // if there is a texture add it to color
    if(doTexture){
      color = vec4(result * textureColor.rgb, textureColor.a);
    }else{
      color = vec4(result, 1.0f);
    }

  }else{
    // if there is a texture add it to color
    if(doTexture){
      color = vec4(textureColor.rgb, textureColor.a);
    }else{
      color = vec4(fragObjectColor, 1.0f);
    }

  }
}
