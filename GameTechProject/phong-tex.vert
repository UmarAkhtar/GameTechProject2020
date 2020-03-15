layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_TexCoord;

out vec3 vertexPosition;
out vec3 norm;
out vec2 ex_TexCoord;

uniform mat4 modelView;
uniform mat4 projection;


void main()
{
	vertexPosition = vec3 (modelView * vec4(in_Position, 1.0));
	
	mat3 normalMatrix = transpose(inverse(mat3(modelView)));
	norm = normalize (normalMatrix * in_Normal);

	ex_TexCoord = in_TexCoord;

	gl_Position = projection * vec4(vertexPosition, 1.0);


}
