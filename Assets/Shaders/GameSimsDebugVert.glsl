#version 400 core

layout(location = 0) in  vec3 position;
layout(location = 1) in  vec4 colour;

uniform vec2 screenSize;
uniform mat4 projMatrix;

out Vertex	{
	vec4 colour;
} OUT;

void main(void)	{
	gl_Position		= projMatrix * vec4(position, 1.0);
	OUT.colour 		= colour;
}