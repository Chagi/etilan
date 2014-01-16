#version 110

//varying vec3 lightPos;dd

void main(void){
	vec3 lightPos = vec3(0.0, 1.0, 5.0);
	float lightRadius = 5.0;
	
	gl_Position = ftransform();
	vec4 col = vec4(0.7, 0.3, 0.7, 0.0);
	float dist = distance(gl_Position.xyz, lightPos);
	
	float denom = (dist/lightRadius + 1.0);
	gl_FrontColor = (gl_Color * col * 2.0)/(denom*denom);
}
