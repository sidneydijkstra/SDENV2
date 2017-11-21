#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec4 color = texture(screenTexture, TexCoords);

    /// inverted colors
    //FragColor = vec4(1 - color.r,1 - color.g,1 - color.b, 1);

    /// black and white
    //float average = (color.r + color.g + color.b) / 3;
    //FragColor = vec4(average,average,average,1);

    /// normal color
    FragColor = color;
}
