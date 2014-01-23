#include <GLFW/glfw3.h>
#include "../Geometry/PointVector.h"
#include <vector>
#include "../Geometry/Maze.h"
#include <iostream>

extern void (*loop_op)(double time);

std::vector<PointVector<4>> cubeRot_cube;
std::vector<int> cubeRot_rotation (3);

void cubeRot_key_fn(GLFWwindow* , int a, int, int c, int){
	if(c != GLFW_PRESS || cubeRot_rotation[0] != 0){
		return;
	}
	switch(a){
	case GLFW_KEY_J:
		cubeRot_rotation[1] = 1;
		cubeRot_rotation[2] = 2;
		cubeRot_rotation[0] = -45;
		break;
	case GLFW_KEY_L:
		cubeRot_rotation[1] = 1;
		cubeRot_rotation[2] = 2;
		cubeRot_rotation[0] = 45;
		break;

	case GLFW_KEY_I:
		cubeRot_rotation[1] = 0;
		cubeRot_rotation[2] = 2;
		cubeRot_rotation[0] = -45;
		break;
	case GLFW_KEY_K:
		cubeRot_rotation[1] = 0;
		cubeRot_rotation[2] = 2;
		cubeRot_rotation[0] = 45;
		break;

	case 85:
		cubeRot_rotation[1] = 2;
		cubeRot_rotation[2] = 3;
		cubeRot_rotation[0] = 45;
		break;
	case 79:
		cubeRot_rotation[1] = 2;
		cubeRot_rotation[2] = 3;
		cubeRot_rotation[0] = -45;
		break;


	}
}

void cubeRot_loop(double ){
	glPushMatrix();
	
	if(cubeRot_rotation[0] > 0){
		cubeRot_rotation[0]--;
		for(PointVector<4>& i: cubeRot_cube){
			if(cubeRot_rotation[1] == 1 && cubeRot_rotation[2] == 2)
				rotate<1,2>(i,3.14159265358979/90.0);
			else if(cubeRot_rotation[1] == 0 && cubeRot_rotation[2] == 2)
				rotate<0,2>(i,3.14159265358979/90.0);
			else if(cubeRot_rotation[1] == 2 && cubeRot_rotation[2] == 3)
				rotate<2,3>(i,3.14159265358979/90.0);
		}
		if(cubeRot_rotation[0] == 0){
			for(auto& i : cubeRot_cube){
				std::cout << i;
			}
		}
	}else if(cubeRot_rotation[0] < 0){
		cubeRot_rotation[0]++;
		for(PointVector<4>& i: cubeRot_cube){
			if(cubeRot_rotation[1] == 1 && cubeRot_rotation[2] == 2)
				rotate<1,2>(i,-3.14159265358979/90.0);
			else if(cubeRot_rotation[1] == 0 && cubeRot_rotation[2] == 2)
				rotate<0,2>(i,-3.14159265358979/90.0);
			else if(cubeRot_rotation[1] == 2 && cubeRot_rotation[2] == 3)
				rotate<2,3>(i,-3.14159265358979/90.0);
		}
	}
	glTranslated(0,0,10);
	glBegin(GL_QUADS);
	for(PointVector<4>& i: cubeRot_cube){
		glVertex4dv((double*)&i);
	}
	glEnd();
	glPopMatrix();
	
}


void cubeRot_init(GLFWwindow* w){
	draw_cube_4(cubeRot_cube,2.0,PointVector<4>{0,0,0,0});
	cubeRot_rotation[0] = 0;
	cubeRot_rotation[1] = 0;
	cubeRot_rotation[2] = 0;
	
	for(auto& i : cubeRot_cube){
		std::cout << i;
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	loop_op = cubeRot_loop;
	glfwSetKeyCallback(w, cubeRot_key_fn);
}
