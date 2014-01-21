#version 120

vec4 project(vec4 position);
vec4 cross4(vec4 a, vec4 b, vec4 c);

vec4 from;
vec4 to;
vec4 over;
vec4 up;

void main(void){
	float color = gl_Position.w;
	gl_Position = project(gl_Vertex);
	color = abs (color - from.w)*5.5;
	
	vec4 col = vec4(color, 1.0, 1.0, 0.0);
	gl_FrontColor = col;
}

vec4 project(vec4 position){
	position.w += 2.0;
	
	from = vec4(0.0, 0.0, 0.0, 0.0);
	to   = vec4(0.0, 0.0, 1.0, 0.0);
	over = vec4(0.0, 0.0, 0.0, 1.0);
	up   = vec4(0.0,-1.0, 0.0, 0.0);
	
	mat4 viewmatrix;
	
	viewmatrix[0] = normalize(to - from);
	viewmatrix[1] = normalize(cross4(up,over,viewmatrix[0]));
	viewmatrix[2] = normalize(cross4(over,viewmatrix[0],viewmatrix[1]));
	viewmatrix[3] = cross4(viewmatrix[0],viewmatrix[1],viewmatrix[2]);
	
	vec4 v = position - from;
	vec4 vp = v*viewmatrix;
	
	float t = 2.0 /tan(3.14/3.0);
	
	position.x = vp.x*t/vp.w;
	position.y = vp.y*t/vp.w;
	position.z = vp.z*t/vp.w;
	position.w = 1.0;
	
	return gl_ProjectionMatrix * gl_ModelViewMatrix * position;
}

vec4 cross4(vec4 u, vec4 v, vec4 w){
	float a,b,c,d,e,f;
	vec4 result;
	
	a = v.x * w.y - v.y * w.x;
	b = v.x * w.z - v.z * w.x;
	c = v.x * w.w - v.w * w.x;
	d = v.y * w.z - v.z * w.y;
	e = v.y * w.w - v.w * w.y;
	f = v.z * w.w - v.w * w.z;
	
	result.x =   u.y*f - u.z*e + u.w*d;
	result.y = - u.x*f + u.z*c - u.w*b;
	result.z =   u.x*e - u.y*c + u.w*a;
	result.w = - u.x*d + u.y*b - u.z*a;
	
	return result;
}
