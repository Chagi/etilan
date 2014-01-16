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
	GLFWwindow* window = glfwCreateWindow(640, 480, "Thuquhux demo", 0, 0);
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
	glBegin(GL_TRIANGLES);
	for(auto& p : lines){
		glVertex4dv((double*)&p);
	}
	glEnd();
}

void cube_test(GLFWwindow* ){
	loop_op = cube_loop;
	lines.push_back({1,1,1,1});
	lines.push_back({0,0,0,0});
	lines.push_back({0,1,2,1});
	glLineWidth(2.5);
}