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
	GLFWwindow* window = glfwCreateWindow(800, 600, "Thuquhux demo", 0, 0);
	if(! window){
		glfwTerminate();
		std::cerr<<"Window creation failed\n";
		std::exit(1);
	}
	glfwMakeContextCurrent(window);
	return window;
}

GLuint shader;
PointVector<4, float> position{0,0,0,0};
PointVector<4, float> lookat{0,0,0,1};
PointVector<4, float> up{1,0,0,0};
PointVector<4, float> over{0,0,1,0};

void initgl(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,0);
	
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	
	shader = InitGLSLShader();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,1,0.1,1000);
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
Maze m{3, 100};

void cube_loop(double ){
	static GLuint p = glGetUniformLocation(shader, "from");
	static GLuint l = glGetUniformLocation(shader, "to");
	static GLuint u = glGetUniformLocation(shader, "up");
	static GLuint o = glGetUniformLocation(shader, "over");
	lookat.make_unit();
	up.make_unit();
	over.make_unit();
	glUniform4fv(p, 1, (float*)&position);
	glUniform4fv(l, 1, (float*)&lookat);
	glUniform4fv(u, 1, (float*)&up);
	glUniform4fv(o, 1, (float*)&over);
	
	glPushMatrix();
	//glRotatef(glfwGetTime()*5, 1,0,0);
	glTranslatef(0,0,0);
	glScalef(0.3,0.3,0.3);
	m.draw();
	glPopMatrix();
}

extern void temp_cube(std::vector<PointVector<4>>& vec);

void key_fn(GLFWwindow*, int a, int, int c, int){
	if(c == GLFW_RELEASE)
		return;
	switch(a){
		case GLFW_KEY_E :
			position += lookat/10.0f;
			break;
		case GLFW_KEY_D :
			position -= lookat/10.0f;
			break;
		case GLFW_KEY_L :
			rotate<2,3>(lookat, 3.14159265/20.0);
			rotate<2,3>(up, 3.14159265/20.0);
			rotate<2,3>(over, 3.14159265/20.0);
			break;
		case GLFW_KEY_J :
			rotate<2,3>(lookat, -3.14159265/20.0);
			rotate<2,3>(up, -3.14159265/20.0);
			rotate<2,3>(over, -3.14159265/20.0);
			break;
		case GLFW_KEY_K :
			rotate<0,2>(lookat, 3.14159265/20.0);
			rotate<0,2>(up, 3.14159265/20.0);
			rotate<0,2>(over, 3.14159265/20.0);
			break;
		case GLFW_KEY_I :
			rotate<0,2>(lookat, -3.14159265/20.0);
			rotate<0,2>(up, -3.14159265/20.0);
			rotate<0,2>(over, -3.14159265/20.0);
			break;
	}
}

void cube_test(GLFWwindow* w){
	loop_op = cube_loop;
	glfwSetKeyCallback(w, key_fn);
	temp_cube(lines);
	glLineWidth(2.5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
