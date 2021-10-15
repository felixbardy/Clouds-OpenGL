#version 330 core
out vec4 FragColor;

in vec3 texPos;
in vec3 ourColor;

uniform float time;

// texture sampler
uniform sampler3D texture1;
uniform sampler3D texture2;
void main()
{
	vec2 tex = mix(texture(texture1, texPos).yz, texture(texture2, texPos).xy, (cos(time)+1)/2);
	float noise = tex.x;
	FragColor = vec4(noise, noise, noise, 1) * vec4(ourColor, 1.0);
}