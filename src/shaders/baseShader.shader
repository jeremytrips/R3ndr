--VERTEX
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main(){
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   ourColor = aColor;
};

--FRAGMENT
#version 460 core
#define PI 3.1415926538

out vec4 FragColor;
in vec3 ourColor;

uniform float timeValue = 0;

void main()
{
    float blueValue = (sin(timeValue));

    FragColor = vec4(ourColor.xyz, 0.1);
};
