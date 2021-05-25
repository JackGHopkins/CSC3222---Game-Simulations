#version 150 core

uniform sampler2D spriteTex;

in Vertex	{
	vec2 texCoord;
} IN;


out vec4 fragColour;

void main(void)	{	
	fragColour = pow(texelFetch(spriteTex, ivec2(IN.texCoord), 0), vec4(2.2));
	
	if(fragColour.a == 0) {
		discard;
	}
	
	//fragColour = vec4(1,0,0,1);
}