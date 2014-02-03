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
#include "Geometry/Maze.h"
#include "Shaders/Shaders.h"
#include "Geometry/Cube.h"
#include "Geometry/DrawHandler.h"

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
	InitGLSLShader();
	
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
	gluLookAt(0,0,-3, 0,0,0, 0,1,0);
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
	GLFWwindow* window = glfwCreateWindow(880, 660, "Thuquhux demo", 0, 0);
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
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,1,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
}

DrawHandler canvas{};
Cube<3> b{{0,0,0,1}, 1.0};
Cube<4> c{{0,0,0,1}, 1.0};

void cube_loop(double ){
	glRotatef(30, -0.6, 1.0, 0.0);
	glColor3d(1.0, 0.0, 0.0);
	canvas.reset();
	b.draw();
	
	glColor3d(1.0, 1.0, 1.0);
	canvas.separate(0.1);
	canvas.rotate(glfwGetTime()/10.0);
	c.draw();
}

void key_fn(GLFWwindow*, int a, int, int c, int){
	if(c == GLFW_RELEASE)
		return;
}

void cube_test(GLFWwindow* w){
	loop_op = cube_loop;
	glfwSetKeyCallback(w, key_fn);
	glLineWidth(1.5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
