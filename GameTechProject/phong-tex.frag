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

#define NR_POINT_LIGHTS 23

uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Material material;
uniform vec3 viewPos;

vec4 result;

    vec4 CalcPointLight(PointLight light, vec3 viewDirection);

void main()
{
   // vec3 viewDirection = normalize(viewPos - vertexPosition);
    vec3 viewDirection = normalize(-vertexPosition);
    
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
     result += CalcPointLight(pointLights[i], viewDirection); 

    FragColor = result;
    
}

vec4 CalcPointLight (PointLight light, vec3 viewDirection)
{

   vec3 viewPosition = normalize (-vertexPosition).xyz;

   float att_distance = distance(vertexPosition, light.position);

   vec3 ambient = light.ambient * texture(material.diffuse, ex_TexCoord).rgb;

   vec3 lightPos = normalize(light.position - vertexPosition);	    //ex_L

   vec3 lightDir = normalize(-vertexPosition).xyz;     

   float diff = max(dot(normalize(norm),normalize(lightPos)), 0.0);
   vec3 diffuse = light.diffuse * diff * texture(material.diffuse, ex_TexCoord).rgb;  

   vec3 reflectDir = normalize(reflect(normalize(-lightPos),normalize(norm)));	                
   //float spec = pow(max(dot(lightDir, reflectDir), 0.0), material.shininess);

   float spec = pow(max(dot(reflectDir, viewPosition), 0.0), material.shininess);

   vec3 specular = light.specular * spec * texture(material.specular, ex_TexCoord).rgb;  

   float ex_attenuation = 1.0f / (light.constant + light.linear * att_distance + 0.01 * att_distance * att_distance);
    
   result = vec4(ambient + diffuse * ex_attenuation, 1.0);

   return result;
}