#version 330 core
// in's
in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTextureCord;

// exit color
out vec4 exitColor;

// color struct
struct Light{
  vec3 color;
  vec3 position;
  vec3 viewPosition;

  float ambientStrength;
  float specularStrength;
};

uniform Light light;

// texture
uniform sampler2D ourTexture;

// mesh color
uniform vec3 fragObjectColor;

// do texture and light vars
uniform bool doLighting;
uniform bool doTexture;

void main(){

    // define texture
    vec4 mytexture;

    if(doTexture){
      // genarate texture
      mytexture = texture(ourTexture, fragTextureCord);
    }

    if(doLighting){ // on light

      // normalize normals
      vec3 norm = normalize(fragNormal);

      // ambient
      float ambientStrength = light.ambientStrength;
      vec3 ambient = ambientStrength * light.color;

      // diffuse
      vec3 lightDir = normalize(light.position - fragPosition);
      float diff = max(dot(lightDir, norm), 0.0f);
      vec3 diffuse = diff * light.color;

      // specular
      float specularStrength = light.specularStrength;
      vec3 viewDir = normalize(light.viewPosition - fragPosition);
      vec3 reflectDir = reflect(-lightDir, norm);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
      vec3 specular = specularStrength * spec * light.color;

      // calculate result
      vec3 result = (ambient + diffuse + specular);

      // add gamma
      float gamma = 1.7;
      result.rgb = pow(result.rgb, vec3(1.0/gamma));

      // set exit color
      if(doTexture){
        exitColor = vec4(result * mytexture.rgb, mytexture.a);
      }else{
        exitColor = vec4(result * fragObjectColor, 1);
      }

    }else{ // on no light
      // set exit color
      if(doTexture){
        exitColor = vec4(mytexture.rgb, mytexture.a);
      }else{
        exitColor = vec4(fragObjectColor, 1);
      }
    }

}
