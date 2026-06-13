#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTextCoords;

out vec3 rgb_color;
out vec2 textCoords;

uniform mat4 transform;

void main()
{
   gl_Position = transform * position;
   rgb_color = aColor;
   textCoords = aTextCoords;
}

#shader fragment
#version 330 core

out vec4 color;
in vec2 textCoords;
in vec4 rgb_color;

uniform vec4 u_Color;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;


void main()
{
	color = mix(texture(ourTexture1,textCoords),texture(ourTexture2,textCoords),0.2)*rgb_color;
};