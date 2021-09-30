#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec3 shaderTexCoord;

// texture sampler
uniform sampler3D texture1;

void main()
{
	vec4 tex = texture(texture1, shaderTexCoord);
	vec3 noise = vec3(mix(tex.y, tex.x, 0.55));
	FragColor = vec4(noise, 1) * vec4(ourColor, 1.0);
}
