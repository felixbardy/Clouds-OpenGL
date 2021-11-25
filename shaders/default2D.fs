#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 shaderTexCoord;

uniform float time;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	//vec2 tex = mix(texture(texture1, shaderTexCoord).xy, texture(texture2, shaderTexCoord).xy, (cos(time)+1)/2.0);
	//float noise = tex.x;
	FragColor = texture(texture1, shaderTexCoord);
}
