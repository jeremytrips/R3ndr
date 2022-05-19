--VERTEX
#version 460 core
layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;

out vec3 pos;


void main(){
    gl_Position = projection * view * vec4(aPos, 1.0f);
}

--FRAGMENT
#version 460 core
out vec4 FragColor;

in vec3 pos;

void main()
{
    FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}