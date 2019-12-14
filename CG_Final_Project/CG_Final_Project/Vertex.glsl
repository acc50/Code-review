#version 330 core

layout(location=0) in vec3 vPos;
layout(location=1) in vec3 vColor;
out vec3 outColor;
uniform mat4 trans;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
	gl_Position=projectionTransform*viewTransform*trans*vec4(vPos.x,vPos.y,vPos.z,1.0);
	//gl_Position=vec4(vPos,1.0);
	outColor=vColor;
}
