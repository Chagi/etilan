#include <GLFW/glfw3.h>
#include "../Geometry/PointVector.h"
#include <vector>

extern void (*loop_op)(double time);

std::vector<PointVector<4>> cubeRot_cube;
std::vector<int> cubeRot_rotation (3);

void cubeRot_key_fn(GLFWwindow* , int a, int, int c, int){
	if(c != GLFW_PRESS || cubeRot_rotation[0] != 0){
		return;
	}
	switch(a){
	case 74:
		cubeRot_rotation[1] = 1;
		cubeRot_rotation[2] = 2;
		cubeRot_rotation[0] = 90;
		break;
	case 76:
		cubeRot_rotation[1] = 1;
		cubeRot_rotation[2] = 2;
		cubeRot_rotation[0] = -90;
		break;

	case 73:
		cubeRot_rotation[1] = 0;
		cubeRot_rotation[2] = 1;
		cubeRot_rotation[0] = 90;
		break;
	case 75:
		cubeRot_rotation[1] = 0;
		cubeRot_rotation[2] = 1;
		cubeRot_rotation[0] = -90;
		break;

	case 85:
		cubeRot_rotation[1] = 1;
		cubeRot_rotation[2] = 3;
		cubeRot_rotation[0] = 90;
		break;
	case 79:
		cubeRot_rotation[1] = 1;
		cubeRot_rotation[2] = 3;
		cubeRot_rotation[0] = -90;
		break;


	}
}

void cubeRot_loop(double ){
	glPushMatrix();

	if(cubeRot_rotation[0] > 0){
		cubeRot_rotation[0]--;
		for(PointVector<4>& i: cubeRot_cube){
			if(cubeRot_rotation[1] == 1 && cubeRot_rotation[2] == 2)
				rotate<1,2>(i,3.141592/45.0);
			else if(cubeRot_rotation[1] == 1 && cubeRot_rotation[2] == 2)
				rotate<0,1>(i,3.141592/45.0);
			else if(cubeRot_rotation[1] == 1 && cubeRot_rotation[2] == 2)
				rotate<1,3>(i,3.141592/45.0);
		}
	}else if(cubeRot_rotation[0] < 0){
		cubeRot_rotation[0]++;
		for(PointVector<4>& i: cubeRot_cube){
			if(cubeRot_rotation[1] == 1 && cubeRot_rotation[2] == 2)
				rotate<1,2>(i,-3.141592/45.0);
			else if(cubeRot_rotation[1] == 1 && cubeRot_rotation[2] == 2)
				rotate<0,1>(i,-3.141592/45.0);
			else if(cubeRot_rotation[1] == 1 && cubeRot_rotation[2] == 2)
				rotate<1,3>(i,-3.141592/45.0);
		}
	}

	glBegin(GL_QUADS);
	for(PointVector<4>& i: cubeRot_cube){
		glVertex4dv((double*)&i);
	}
	glEnd();
	glPopMatrix();
}


void cubeRot_init(GLFWwindow* w){
	draw_cube_4(cubeRot_cube,1.0,PointVector<>{0,0,0,0});
	cubeRot_rotation[0] = 0;
	cubeRot_rotation[1] = 0;
	cubeRot_rotation[2] = 0;

	loop_op = cubeRot_loop(5.0);
	glfwSetKeyCallback(w, cubeRot_key_fn);
}
