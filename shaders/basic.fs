#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec3 shaderTexCoord;

uniform float time;

// texture sampler
uniform sampler3D texture1;
void main()
{
	vec4 tex = texture(texture1, shaderTexCoord);
	float noise = tex.x;
	FragColor = vec4(noise, noise, noise, 1) * vec4(ourColor, 1.0);
}