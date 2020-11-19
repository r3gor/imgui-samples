#version 330

layout (location = 0) in vec3 vertPos;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 varColor;

void main(){
	gl_Position = proj_matrix * mv_matrix * vec4(vertPos,1.0);
	varColor = vec4(vertPos, 1.0) * 0.5 + vec4(0.4, 0.4, 0.4, 0.4);
}