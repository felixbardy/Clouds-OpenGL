#version 330 core


out vec2 position;

void main( )
{
    vec2 positions[3]= vec2[3]( vec2(-1,-3), vec2(3, 1), vec2(-1, 1) );
    
    position= positions[gl_VertexID];
    gl_Position= vec4(positions[gl_VertexID], 0, 1);
}
