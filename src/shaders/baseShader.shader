--VERTEX
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model = mat4(1);

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}

--FRAGMENT
#version 330 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0, 0.3, 0.8, 1.0);
}