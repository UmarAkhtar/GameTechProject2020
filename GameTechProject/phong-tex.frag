#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 vertexPosition;  
in vec3 ex_N;  
in vec2 ex_TexCoord;
in vec3 ex_L;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

in float ex_attenuation;

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, ex_TexCoord).rgb;
  	
    // diffuse 
    vec3 norm = normalize(ex_N);
    vec3 lightDir = normalize(light.position - vertexPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, ex_TexCoord).rgb;  
    
    // specular
  //  vec3 viewDir = normalize(viewPos - vertexPosition); // already been done in vert, same as light.xyz - vertpos
    vec3 reflectDir = normalize(reflect(normalize(-ex_L),normalize(ex_N)));	
    float spec = pow(max(dot(ex_L, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, ex_TexCoord).rgb;  
        
    vec4 result = vec4(ambient + diffuse  * ex_attenuation, 1.0);
    FragColor = result;
} 