#version 330 core

//��ü���� �޾ƿ���

uniform vec3 objectColor;

out vec4 Fragcolor;
in vec3 outColor;


void main()
{
	Fragcolor =vec4(objectColor,1.0f);	

}