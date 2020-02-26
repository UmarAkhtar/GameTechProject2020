// phong-tex.vert
// Vertex shader for use with a Phong or other reflection model fragment shader
// Calculates and passes on V, L, N vectors for use in fragment shader, phong2.frag
#version 330

uniform float attenuationConst;
uniform float attenuationLinear;
uniform float attenuationQuadratic;


uniform mat4 view;
uniform mat4 projection;
uniform vec4 lightPosition;
uniform mat4 model;
//uniform mat3 normalmatrix;

in  vec3 in_Position;
in  vec3 in_Normal;
out vec3 ex_N;
out vec3 ex_V;
out vec3 ex_L;

in vec2 in_TexCoord;
out vec2 ex_TexCoord;
out vec3 vertexPosition;

out float ex_attenuation;
out float ex_dist;

																									// multiply each vertex position by the MVP matrix and find V, L, N vectors for the fragment shader
void main(void) {


	
	//vec4 vertexPosition = view * vec4(in_Position,1.0);										// vertex into eye coordinates

	vertexPosition = vec3(model  * vec4(in_Position,1.0));	

	//vec4 mylightPosition = view * vec4(lightPosition);

	
	ex_V = normalize(-vertexPosition).xyz;															// Find V - in eye coordinates, eye is at (0,0,0)


	mat3 normalmatrix = transpose(inverse(mat3(view)));										// surface normal in eye coordinates taking the rotation part of the modelview matrix to generate the normal matrix
																									//(if scaling is includes, should use transpose inverse modelview matrix!) this is somewhat wasteful in compute time and should really be part of the cpu program,
																									// giving an additional uniform input
	ex_N = normalize(normalmatrix * in_Normal);

	
	ex_L = normalize(lightPosition.xyz - vertexPosition.xyz);										// L - to light source from vertex

	ex_TexCoord = in_TexCoord;

   gl_Position = projection * vec4(vertexPosition,1.0);

	float att_distance = distance(vec4(vertexPosition,1.0), lightPosition);

	ex_attenuation = (1.0 / (1.0 + 0.2 * att_distance + 0.01 * att_distance * att_distance));


	
}

//attenuation =  1/ constant attenuation factor + (linear attenuation factor * distance) + (quadratic attenuation factor * (distance * distance)
// distance = distance between light source and surface being shaded. 
// kc = 1, kl = 0, kq = 0
//kc = constant attenuation factor
// kl = linear attenuation factor 
//kq = quadtratic attenuation factor.














