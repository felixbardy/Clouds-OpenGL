#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec3 TexCoord;

// texture sampler
uniform sampler3D texture1;



void main()
{
    gl_FragColor = vec4(worley(TexCoord, false, false, false).xyz, 1);  
}