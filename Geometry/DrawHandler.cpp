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
	v[0] = v[0]* cos(angle) + v[1]* sin(angle);
	v[1] = v[1]* cos(angle) - v[0]* sin(angle);
}

namespace{
	void rotate_point(PointVector<4>& point, PointVector<> axis, double angle){
		axis.make_unit();
		const PointVector<> r1{cos(angle) + axis.getdx()*axis.getdx()*(1 - cos(angle)),
		                       axis.getdx()*axis.getdy()*(1 - cos(angle)) - axis.getdz()*sin(angle),
		                       axis.getdx()*axis.getdz()*(1 - cos(angle)) + axis.getdy()*sin(angle)};
		const PointVector<> r2{axis.getdy()*axis.getdx()*(1 - cos(angle)) + axis.getdz()*sin(angle),
		                       cos(angle) + axis.getdy()*axis.getdy()*(1 - cos(angle)),
		                       axis.getdy()*axis.getdz()*(1 - cos(angle)) - axis.getdx()*sin(angle)};
		const PointVector<> r3{axis.getdz()*axis.getdx()*(1 - cos(angle)) - axis.getdy()*sin(angle),
		                       axis.getdz()*axis.getdy()*(1 - cos(angle)) + axis.getdx()*sin(angle),
		                       cos(angle) + axis.getdz()*axis.getdz()*(1 - cos(angle))};
		const PointVector<4> tmp = point;
		point[0] = PointVector<>::mul_comp(r1, tmp).sum_comp();
		point[1] = PointVector<>::mul_comp(r2, tmp).sum_comp();
		point[2] = PointVector<>::mul_comp(r3, tmp).sum_comp();
	}
}

void DrawHandler::drawQuad(PointVector<4> a, PointVector<4> b, PointVector<4> c, PointVector<4> d){
	glPushMatrix();
	glBegin(GL_QUADS);
	
	a = (a - eyepos) * separation + translation;
	b = (b - eyepos) * separation + translation;
	c = (c - eyepos) * separation + translation;
	d = (d - eyepos) * separation + translation;
	
	rotate_point(a, {0,0,1}, rotation);
	rotate_point(b, {0,0,1}, rotation);
	rotate_point(c, {0,0,1}, rotation);
	rotate_point(d, {0,0,1}, rotation);
	
	glVertex4d(a[0], a[1], a[2], a[3]);
	glVertex4d(b[0], b[1], b[2], b[3]);
	glVertex4d(c[0], c[1], c[2], c[3]);
	glVertex4d(d[0], d[1], d[2], d[3]);
	
	glEnd();
	glPopMatrix();
}
