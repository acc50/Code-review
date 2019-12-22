
#version 330 core

in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

uniform vec3 LightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
void main()
{

	vec3 ambientLight = vec3(0.3f,0.3f,0.3f);		//���� ���� ����
	vec3 ambient = ambientLight * lightColor;		//���� ���� ��
	vec3 normalVector = Normal;
	vec3 lightDir = normalize(LightPos - FragPos);	//������ �Ի簢
	float diffuseLight = max(dot(normalVector,lightDir),0.0f);

	vec3 diffuse=diffuseLight*lightColor;
	vec3 result=(ambient+diffuse)*objectColor;
	FragColor=vec4(result,1.0f);
	//FragColor=vec4(1.0f,0.0f,0.0f,1.0f);
}