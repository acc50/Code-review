
#version 330 core

in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;


uniform vec3 objectColor;
uniform vec3 LightPos;
uniform vec3 lightColor;

void main()
{

	vec3 ambientLight = vec3(0.001f,0.001f,0.001f);		//전역 조명 세기
	vec3 ambient = ambientLight * lightColor;		//전역 조명 값
	vec3 normalVector = Normal;
	vec3 lightDir = normalize(LightPos - FragPos);	//조명의 입사각
	float diffuseLight = max(dot(normalVector,lightDir),0.0f);

	vec3 diffuse=diffuseLight*lightColor;
	vec3 result=(ambient+diffuse)*objectColor;
	FragColor=vec4(result,1.0f);
	//FragColor=vec4(1.0f,0.0f,0.0f,1.0f);
}