#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec3 TexCoord;

// texture sampler
uniform sampler3D texture1;

void main()
{
	vec4 tex = texture(texture1, TexCoord);

	
	if(tex.y > 0)
	{
		FragColor = vec4(1, 0, 0, 1.0) * vec4(ourColor, 1.0);
	}
	else
	{
		FragColor = vec4(tex.x, tex.x, tex.x, tex.x) * vec4(ourColor, 1.0);
	}
	
}