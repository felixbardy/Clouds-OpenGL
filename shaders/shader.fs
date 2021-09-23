#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec3 TexCoord;

// texture sampler
uniform sampler3D texture1;

void main()
{
	vec4 tex = texture(texture1, TexCoord);
	FragColor = vec4(tex.y, tex.y, tex.y, 1) * vec4(ourColor, 1.0);
}