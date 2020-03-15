#version 330


layout (location = 0) in vec3 in_Position;		// keep -apos
layout (location = 1) in vec3 in_Normal;		//keep - anormal
layout (location = 2) in vec2 in_TexCoord;		//keep -atextcoord

uniform mat4 view;				//keep	
uniform mat4 projection;		//keep
uniform mat4 modelView;			//keep = model

out vec3 vertexPosition;		//keep =  fragPos
out vec3 ex_N;
out vec2 ex_TexCoord;

																									// multiply each vertex position by the MVP matrix and find V, L, N vectors for the fragment shader
void main(void) {

	vertexPosition = vec3(modelView  * vec4(in_Position,1.0));	

	mat3 normalmatrix = transpose(inverse(mat3(modelView)));										// surface normal in eye coordinates taking the rotation part of the modelview matrix to generate the normal matrix
																									//(if scaling is includes, should use transpose inverse modelview matrix!) this is somewhat wasteful in compute time and should really be part of the cpu program,
																									// giving an additional uniform input
	ex_N = normalize(normalmatrix * in_Normal);
	
	ex_TexCoord = in_TexCoord;

    gl_Position = projection * vec4(vertexPosition,1.0);

	
	
}
