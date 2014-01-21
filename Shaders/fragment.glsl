#version 120

void main(void){
	float maxdist = 7;
	float mindist = 0;
	vec4 dist = gl_Color - gl_SecondaryColor;
	float col = (dist.w - mindist)/maxdist;
	vec4 color;
	if(col > 1)
		color = vec4(1.0, 1.0, 1.0, 1.0);
	else if(col > 0){
		color = vec4(col, 1.0 - col, 1.0 - col, 1.0);
		color = color/max(col, 1.0 - col);
	}
	else
		color = vec4(1.0, 0.0, 0.0, 0.0);
	gl_FragColor = color;
}
