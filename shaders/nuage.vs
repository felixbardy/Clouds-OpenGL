#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;


uniform mat4 mvpMatrix;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 position;

void main()
{
    gl_Position = mvpMatrix * vec4(aPos, 1.0);
    position = vec3(gl_Position.xy, gl_Position.w);
}