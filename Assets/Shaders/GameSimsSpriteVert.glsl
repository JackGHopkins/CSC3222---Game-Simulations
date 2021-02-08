#version 400 core

layout(location = 0) in  vec3 position;
layout(location = 2) in  vec2 texCoord;

uniform vec2 screenSize;

uniform vec2 spritePos;
uniform vec2 spriteSize;

uniform vec2 texPos;
uniform vec2 texSize;

uniform mat4 projMatrix;

uniform int invertX;

out Vertex	{
	vec2 texCoord;
} OUT;

void main(void)	{
	vec3 vertexPos = (position * vec3(spriteSize.xy, 1)) + vec3(spritePos.xy, 0);
	
	gl_Position		= projMatrix * vec4(vertexPos, 1.0);
	
	vec2 tempTex = texCoord;
	
	if(invertX == 1) {
		tempTex.x = 1.0f - tempTex.x;
	}
	
	OUT.texCoord	= (tempTex * vec2(texSize)) + vec2(texPos);
}