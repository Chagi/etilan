#version 120

varying vec4 w_pos;
varying float w_test;
varying vec4 cull_pos;

void main(void){
	if(w_pos.w < 0.0)
		discard;
	
	int count = 0;
	if(w_pos.x > 1 || w_pos.x < -1)
		count++;
	if(w_pos.y > 1 || w_pos.y < -1)
		count++;
	if(w_pos.z > 1 || w_pos.z < -1)
		count++;
	if(w_pos.w > 1 || w_pos.w < -1)
		count++;
	
	if(count > 1)
		count++;//discard;
	
	vec4 color = vec4(1.0, 0.0, 0.0, 1.0);
	gl_FragColor = gl_Color /(w_pos.w*2) + color;
	
	
}
