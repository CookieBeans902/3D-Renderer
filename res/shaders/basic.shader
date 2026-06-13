#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 aTextCoords;

out vec2 textCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * model * position;
   textCoords = aTextCoords;
}

#shader fragment
#version 330 core

out vec4 color;
in vec2 textCoords;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;


void main()
{
	color = mix(texture(ourTexture1,textCoords),texture(ourTexture2,textCoords),0.2);
};