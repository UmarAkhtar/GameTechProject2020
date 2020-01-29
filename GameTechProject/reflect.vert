// phong-tex.vert
// Vertex shader for use with a Phong or other reflection model fragment shader
// Calculates and passes on V, L, N vectors for use in fragment shader, phong2.frag
#version 330

uniform float attConstant;
uniform float attLinear;
uniform float attQuadratic;

uniform mat4 modelview;
uniform mat4 projection;

uniform vec4 lightPosition;

uniform mat4 modelMatrix;
uniform vec3 cameraPos;


in  vec3 in_Position;
in  vec3 in_Normal;
out vec3 ex_N;
out vec3 ex_V;
out vec3 ex_L;

in vec2 in_TexCoord;
out vec2 ex_TexCoord;

out float ex_attenuation;
out float ex_dist;

out vec3 ex_WorldNorm;
out vec3 ex_WorldView;
																									// multiply each vertex position by the MVP matrix and find V, L, N vectors for the fragment shader
void main(void) {

	
	vec4 vertexPosition = modelview * vec4(in_Position,1.0);										// vertex into eye coordinates

	
	ex_V = normalize(-vertexPosition).xyz;															// Find V - in eye coordinates, eye is at (0,0,0)


	mat3 normalmatrix = transpose(inverse(mat3(modelview)));										// surface normal in eye coordinates taking the rotation part of the modelview matrix to generate the normal matrix
																									//(if scaling is includes, should use transpose inverse modelview matrix!) this is somewhat wasteful in compute time and should really be part of the cpu program,
																									// giving an additional uniform input
	ex_N = normalize(normalmatrix * in_Normal);

	
	ex_L = normalize(lightPosition.xyz - vertexPosition.xyz);										// L - to light source from vertex

	ex_TexCoord = in_TexCoord;

  

	float att_distance = distance(vertexPosition, lightPosition);

	vec3 worldPos = (modelMatrix * vec4(in_Position,1.0)).xyz;		
	
	mat3 normalworldmatrix = transpose(inverse(mat3(modelMatrix))); //modelview

	ex_WorldNorm = normalworldmatrix * in_Normal;

	ex_WorldView = cameraPos - worldPos;

	ex_attenuation = (1.0 / (attConstant + attLinear * att_distance + attQuadratic * att_distance * att_distance));
  gl_Position = projection * vertexPosition;

	}