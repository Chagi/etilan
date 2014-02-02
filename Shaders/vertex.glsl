#version 120

varying vec4 pos;

void main(void){
	pos = gl_Vertex;
	gl_FrontColor = gl_Color;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
