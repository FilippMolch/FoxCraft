#version 450 core

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D tex;
uniform vec3 uLightPos;

vec3 calcPointLight(vec3 Normal, vec3 lightColor, vec3 lightPos, vec3 objectColor)
{
	float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;
  	
    // Диффузная составляющая 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float distance = length(lightPos);
    float attenuation = 1.0 / (1.0f + 0.0014f * distance + 0.000007f * (distance * distance));
            
    ambient *= attenuation; 
    diffuse *= attenuation;
    //specular *= attenuation;

    vec3 result = (ambient + diffuse) * objectColor;
	return result;
}

vec3 calcSun(vec3 Normal, vec3 lightColor, vec3 lightPos, vec3 objectColor){
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // Диффузная составляющая 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            
    vec3 result = (ambient + diffuse) * objectColor;
    return result;
}

void main()
{
    //texture2D(tex, vTexCoord)
	FragColor = texture2D(tex, vTexCoord);// + vec4(calcSun(vNormal, vec3(0.5f), uLightPos, vec3(1.0f)), 1.0f);
} 