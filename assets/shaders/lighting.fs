#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D texture1;

// Output fragment color
out vec4 finalColor;

float gauss(float x, float sigma)
{
    return exp(-(x*x) / (2.0 * sigma * sigma));
}

void main()
{
    
    finalColor = texture(texture0, fragTexCoord) * texture(texture1, fragTexCoord);

}