#version 330 core

out vec4 color;
in vec2 textCoords;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;


void main()
{
	color = mix(texture(ourTexture1,textCoords),texture(ourTexture2,textCoords),0.2);
};