#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 vertexPosition;
in vec3 norm;
in vec2 ex_TexCoord;

#define NR_POINT_LIGHTS 4

uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Material material;
uniform vec3 viewPos;

vec3 result;

    vec3 CalcPointLight(PointLight light, vec3 viewDirection);

void main()
{
    vec3 viewDirection = normalize(viewPos - vertexPosition);
    
      for(int i = 0; i < NR_POINT_LIGHTS; i++)
      result += CalcPointLight(pointLights[i], viewDirection); 

      FragColor = vec4 (result, 1.0);
    
}

vec3 CalcPointLight (PointLight light, vec3 viewDirection)
{

    vec3 viewDirectionTest = normalize(light.position - vertexPosition);

    vec3 lightDirection = normalize (light.position - vertexPosition);

    float diff = max(dot(norm, lightDirection) , 0.0);

    vec3 reflectDir = normalize(reflect(normalize(-lightDirection),normalize(norm)));
    
    float spec = pow(max(dot(viewDirectionTest, reflectDir), 0.0), material.shininess);

    float distance = length(light.position - vertexPosition);

    float attenuation = 1.0 / (light.constant + light.linear * distance + 0.01 * (distance * distance));    
    
    vec3 ambient = light.ambient * texture(material.diffuse, ex_TexCoord).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, ex_TexCoord).rgb; 
    vec3 specular = light.specular * spec * texture(material.specular, ex_TexCoord).rgb;  

    ambient *= attenuation;
    diffuse *= attenuation ;
   // specular *= attenuation;
    return (ambient + diffuse + specular); 
    

}