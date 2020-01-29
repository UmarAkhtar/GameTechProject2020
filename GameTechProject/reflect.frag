// Phong fragment shader phong-tex.frag matched with phong-tex.vert
#version 330

// Some drivers require the following
precision highp float;

struct lightStruct
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

struct materialStruct
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform lightStruct light;
uniform materialStruct material;


in float ex_attenuation;

in vec3 ex_N;
in vec3 ex_V;
in vec3 ex_L;
in vec2 ex_TexCoord;
layout(location = 0) out vec4 out_Color;

in vec3 ex_WorldNorm;
in vec3 ex_WorldView;


uniform samplerCube cubeMap;
uniform sampler2D texMap;

uniform float attConst;
uniform float attLinear;
uniform float attQuadratic;
 
void main(void) {
    
	
	vec4 ambientI = light.ambient * material.ambient;											// Ambient intensity

	
	vec4 diffuseI = light.diffuse * material.diffuse;											// Diffuse intensity
	
	diffuseI = diffuseI * max(dot(normalize(ex_N),normalize(ex_L)),0);
	
	vec3 R = normalize(reflect(normalize(-ex_L),normalize(ex_N)));								// Specular intensity. Calculate R - reflection of light

	vec4 specularI = light.specular * material.specular;
	
	specularI = specularI * pow(max(dot(R,ex_V),0), material.shininess);

																								// Fragment colour

	vec4 tmp_Color = (diffuseI + specularI); //attenuation does not affect ambient light

	
	vec4 litColour = ambientI + vec4(tmp_Color.rgb * ex_attenuation, 1.0);

	//out_Color = litColor * texture2D(textureUnit0, ex_TexCoord);

	vec3 reflectTexCoord = reflect(-ex_WorldView, normalize(ex_WorldNorm));

	//out_Color = texture(cubeMap, reflectTexCoord) * texture(texMap, ex_TexCoord) * litColour ;

	out_Color = vec4(reflectTexCoord,1.0f);
	}