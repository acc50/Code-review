
#version 330 core

in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

uniform vec3 LightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform float lightRange;

void main()
{

	vec3 ambientLight = vec3(1.f,1.0f,1.0f);		//전역 조명 세기
	vec3 ambient = ambientLight * lightColor;		//전역 조명 값

	vec3 normalVector = Normal;

	float dist = sqrt(pow(lightPos.x - FragPos.x, 2.f) + 
	pow(lightPos.y - FragPos.y, 2.f) + pow(lightPos.z - FragPos.z, 2.f)) ;
	
	vec4 result = vec4(0.7f,0.7f,0.7f,1.0f);
	if(dist < lightRange)
	{
		vec3 lightDir = normalize(lightPos - FragPos);	//조명의 입사각
		float diffuseLight = max(dot(normalVector,lightDir),0.0f);

		vec3 diffuse = diffuseLight * lightColor;

		result = vec4((ambient + diffuse),1.0f);
	}
	FragColor=vec4(result,1.0f);
	//FragColor=vec4(1.0f,0.0f,0.0f,1.0f);
}