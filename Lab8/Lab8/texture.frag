#version 330 core

out vec4 fragColour;

in vec2 tex;

uniform sampler2D Texture;

void main()
{
    fragColour = texture(Texture, tex);
}
