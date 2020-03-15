#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light
{
	vec3 position;

	float attenuationConst;
	float attenuationLinear;
	float attenuationQuadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define NR_LIGHTS 4

uniform Light lights[NR_LIGHTS];

in vec3 vertexPosition;  //fragPos
in vec3 ex_N;           //Normal
in vec2 ex_TexCoord;
  
uniform vec3 viewPos;
uniform Material material;

vec4 result;
vec4 tmpColour;
vec4 litColour;


vec3 CalcLights(Light light, vec3 vertPos);

void main()
{
   vec3 norm = normalize(ex_N);
   //vec3 lightDir = normalize(lights.position - vertexPosition);
   
   for(int i = 0; i < NR_LIGHTS; i++)
      result += CalcLights(lights[i], vertexPosition);

       FragColor = result;
      
} 
 

vec3 CalcLights(Light light, vec3 vertPos)
{
    
       vec3 ambient = light.ambient * texture(material.diffuse, ex_TexCoord).rgb;

       vec3 norm = normalize(ex_N);
       vec3 lightDir = normalize(light.position - vertexPosition);

       float diff = max(dot(norm, lightDir), 0.0);

       vec3 diffuse = light.diffuse * diff * texture(material.diffuse, ex_TexCoord).rgb;  

       vec3 reflectDir = normalize(reflect(normalize(-lightDir),normalize(ex_N)));

       float spec = pow(max(dot(lightDir, reflectDir), 0.0), material.shininess);

       vec3 specular = light.specular * spec * texture(material.specular, ex_TexCoord).rgb;  

       float att_distance = distance(vec4(vertexPosition,1.0), vec4(light.position, 1.0));
  
       float ex_attenuation = (1.0 / (light.attenuationConst + light.attenuationLinear * att_distance +  0.01f * att_distance * att_distance));
       
       vec4 test = vec4(ambient + diffuse  * ex_attenuation, 1.0);
       return (test);
}
