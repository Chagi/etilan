/*
 * File: DrawHandler.cpp
 * Author: Elias Forsberg
 *
 * Created on: February 1, 2014, 16:12
 */

#include <GLFW/glfw3.h>
#include "DrawHandler.h"

DrawHandler::DrawHandler():
	separation{0.4},
	translation{0.0, 0.0, 0.0, 0.0},
	retina_size{1.0},
	color{1.0, 1.0, 1.0, 1.0},
	eyepos{0.0, 0.0, 0.0, 0.0},
	lookat{0.0, 0.0, 1.0, 0.0}
{}

void DrawHandler::reset(){
	separation = 1.0;
	translation = PointVector<4>{0.0, 0.0, 0.0, 0.0};
	rotation = 0.0;
	eyepos = PointVector<4>{0.0, 0.0, 0.0, 0.0};
}

void DrawHandler::separate(double sep){
	separation = 1.0 - sep;
}

void DrawHandler::translate(PointVector<4> pos){
	translation = pos;
}

void DrawHandler::rotate(double angle){
	rotation = angle;
}

void DrawHandler::moveCamera(PointVector<4> pos){
	eyepos = pos;
}

void rotateXY(PointVector<4>& v, double angle){
	v[0] = v[0]*cos(angle) + v[1]*-sin(angle);
	v[1] = v[0]*sin(angle) + v[1]* cos(angle);
}

void DrawHandler::drawQuad(PointVector<4> a, PointVector<4> b, PointVector<4> c, PointVector<4> d){
	glPushMatrix();
	glBegin(GL_QUADS);
	
	::rotateXY(translation, rotation);
	::rotateXY(a, rotation);
	::rotateXY(b, rotation);
	::rotateXY(c, rotation);
	::rotateXY(d, rotation);
	
	a = (a - eyepos) * separation + translation;
	b = (b - eyepos) * separation + translation;
	c = (c - eyepos) * separation + translation;
	d = (d - eyepos) * separation + translation;
	
	glVertex4d(a[0], a[1], a[2], a[3]);
	glVertex4d(b[0], b[1], b[2], b[3]);
	glVertex4d(c[0], c[1], c[2], c[3]);
	glVertex4d(d[0], d[1], d[2], d[3]);
	
	glEnd();
	glPopMatrix();
}
