#version 330 core

//물체색깔 받아오기

uniform vec3 objectColor;

out vec4 Fragcolor;
in vec3 outColor;


void main()
{
	Fragcolor =vec4(objectColor,1.0f);	

}