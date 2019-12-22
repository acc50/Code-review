#version 330 core

layout(location=0) in vec3 vPos;

layout(location=1) in vec3 vNormal;


out vec3 FragPos;
out vec3 Normal;

uniform mat4 trans;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
	
	gl_Position=projectionTransform*viewTransform*trans*vec4(vPos.x,vPos.y,vPos.z,1.0);
	FragPos=vec3(trans*vec4(vPos,1.0f));
	Normal=normalize(vNormal);
}



