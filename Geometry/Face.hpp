/*
 * File: Face.hpp
 * Author: Elias Forsberg
 *
 * Created on: February 1, 2014, 15:03
 */

#ifndef FACE_HPP
#define FACE_HPP

#include "Face.h"
#include "DrawHandler.h"

DrawHandler canvas{};

Face<2>::Face(PointVector<4> position, PointVector<4> plane1, PointVector<4> plane2):
	pos{position},
	p1{plane1},
	p2{plane2}
{}

void Face<2>::draw(){
	glPushMatrix();
		auto a = ( p1 - p2)/2.0;
		auto b = ( p1 + p2)/2.0;
		auto c = (-p1 + p2)/2.0;
		auto d = (-p1 - p2)/2.0;
		canvas.translate(pos);
		canvas.separate(0.1);
		canvas.drawQuad(a, b, c, d);
	glPopMatrix();
}

Face<3>::Face(PointVector<4> position, PointVector<4> plane1,
                                       PointVector<4> plane2,
                                       PointVector<4> plane3):
	pos{position},
	p{plane1, plane2, plane3}
{}

void Face<3>::draw(){
	auto a = ( p[0] + p[1] + p[2])/2.0;
	auto b = (-p[0] + p[1] + p[2])/2.0;
	auto c = (-p[0] + p[1] - p[2])/2.0;
	auto d = ( p[0] + p[1] - p[2])/2.0;
	auto e = ( p[0] - p[1] + p[2])/2.0;
	auto f = (-p[0] - p[1] + p[2])/2.0;
	auto g = (-p[0] - p[1] - p[2])/2.0;
	auto h = ( p[0] - p[1] - p[2])/2.0;
	canvas.translate(pos);
	canvas.separate(0.1);
	canvas.drawQuad(a, b, c, d);
	canvas.drawQuad(a, b, f, e);
	canvas.drawQuad(e, f, g, h);
	canvas.drawQuad(g, h, d, c);
}

#endif /* FACE_H */
