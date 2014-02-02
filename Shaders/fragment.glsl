#version 120

varying vec4 pos;

void main(void){
	vec3 p = pos.xyz / pos.w;
	if(any(lessThan(p, vec3(-0.5))))
		discard;
	if(any(greaterThan(p, vec3(0.5))))
		discard;
	gl_FragColor = gl_Color;
}
