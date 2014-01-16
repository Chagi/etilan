#version 120

vec4 project(vec4 position);

void main(void){
	gl_Position = project(gl_Vertex);
	
	vec3 lightPos = vec3(0.0, 1.0, 5.0);
	vec4 col = vec4(0.7, 0.3, 0.7, 0.0);
	
	float dist = distance(gl_Position.xyz, lightPos);
	float lightRadius = 5.0;
	float denom = (dist/lightRadius + 1.0);
	gl_FrontColor = (gl_Color * col * 2.0)/(denom*denom);
}

vec4 project(vec4 position){
	float r4 = 2;
	
	vec4 frompoint = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 topiont   = vec4(0.0, 0.0, 1.0, 0.0);
	vec4 overpoint = vec4(0.0, 0.0, 0.0, 1.0);
	
	mat4 viewmatrix = mat4(1.0, 0.0, 0.0, 0.0,
	                       0.0, 1.0, 0.0, 0.0, 
	                       0.0, 0.0, 1.0, 0.0, 
	                       0.0, 0.0, 0.0, 1.0);
	
	position = (position - frompoint) * viewmatrix;
	position = vec4(position.x/r4, position.y/r4, position.z/r4, 1.0);
	return gl_ProjectionMatrix * gl_ModelViewMatrix * position;
}
