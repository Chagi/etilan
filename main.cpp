/*
 * File: main.cpp
 * Authors: Charles Gilljam, Elias Forsberg
 *
 * Created on: January 16, 2014, 08:25
 */

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cmath>

#include "Geometry/PointVector.h"
#include "Shaders/Shaders.h"

void demo_loop(GLFWwindow* widow);
GLFWwindow* loadglfw();
void initgl();

void (*loop_init)(GLFWwindow*);
void (*loop_op)(double time);

void cube_test(GLFWwindow* w);

int main (){
	loop_init = cube_test;
	
	auto window = loadglfw();
	glewInit();
	initgl();
	
	demo_loop(window);
	
	glfwDestroyWindow(window);
	glfwTerminate();
}

void fix_gl_stuff(GLFWwindow* window){
	glfwSwapBuffers(window);
	glfwPollEvents();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,-2, 0,0,1, 0,1,0);
}

double get_time(){
	static double prev_time = glfwGetTime();
	double delta_time = glfwGetTime() - prev_time;
	prev_time = glfwGetTime();
	return delta_time;
}

void demo_loop(GLFWwindow* window){
	loop_init(window);
	while(!glfwWindowShouldClose(window)){
		double delta_time = get_time();
		fix_gl_stuff(window);
		loop_op(delta_time);
	};
}

GLFWwindow* loadglfw(){
	if(!glfwInit()){
		std::cerr<<"OpenGL initialization failed\n";
		std::exit(1);
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Thuquhux demo", 0, 0);
	if(! window){
		glfwTerminate();
		std::cerr<<"Window creation failed\n";
		std::exit(1);
	}
	glfwMakeContextCurrent(window);
	return window;
}

void initgl(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,0);
	
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	
	InitGLSLShader();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50,1,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
}

Geometry::Vector<2, double> easy_mouse(GLFWwindow* w){
	double x = 0, y = 0;
	int dx = 0, dy = 0;

	glfwGetCursorPos(w,&x,&y);
	glfwGetWindowSize(w, &dx, &dy);

	x = (x/double(dx) - x/(2.0*dx))*2;
	y = (y/double(dy) - y/(2.0*dy))*2;
	x = -(x - 0.5)*2;
	y = -(y - 0.5)*2;
	
	return Geometry::Vector<2, double>{x,y};
}

std::vector<Geometry::Vector<4, double>> lines;

void cube_loop(double ){
	glPushMatrix();
	glTranslatef(0,0,-1);
	glRotated(glfwGetTime()*3, 0,1,0);
	
	for(int i = 0; i*24 < (signed)lines.size(); i++){
		static double colors[][3] = {{0,0,1},
		                             {0,1,0},
		                             {1,0,0},
		                             {0,1,1},
		                             {1,1,0},
		                             {1,0,1},
		                             {1,1,1},
		                             {0.5,0.5,0.5}};
		glPushMatrix();
		glColor3dv(colors[i]);
			
		glBegin(GL_QUADS);
		for(int n = 0; n < 24; n++){
			glVertex4dv((double*)&lines[i*24 + n]);
		}
		glEnd();
		
		glPopMatrix();
	}
	glPopMatrix();
}

extern void temp_cube(std::vector<PointVector<4>>& vec);

void key_fn(GLFWwindow*, int a, int, int c, int){
	if(c == GLFW_RELEASE)
		return;
	if(a == 65 || a == 83){
		for(auto& l : lines){
			rotate<0,3>(l, (74-a)/90);
		}
		std::cout<<a<<"\n";
	}
	if(a == 67 || a == 70){
		for(auto& l : lines){
			rotate<2,3>(l, (68.5-a)/15);
		}
	}
}

void cube_test(GLFWwindow* w){
	loop_op = cube_loop;
	glfwSetKeyCallback(w, key_fn);
	temp_cube(lines);
	glLineWidth(2.5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
