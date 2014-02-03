/*
 * File: Face.h
 * Author: Elias Forsberg
 *
 * Created on: February 1, 2014, 15:03
 */
 
#ifndef FACE_H
#define FACE_H

#include "PointVector.h"

template<int Dim>
class Face{};

template<>
class Face<2> {
public:
	Face() = default;
	Face(PointVector<4> position, PointVector<4> plane1, PointVector<4> plane2);
	
private:
	PointVector<4> pos;
	PointVector<4> p1;
	PointVector<4> p2;

public:
	void draw();
	void rotate(int a, int b);
};

template<>
class Face<3> {
public:
	Face() = default;
	Face(PointVector<4> position, PointVector<4> plane1,
	                              PointVector<4> plane2,
	                              PointVector<4> plane3);
private:
	PointVector<4> pos;
	PointVector<4> p[3];

public:
	void draw();
};

#endif /* FACE_H */

#include "Face.hpp"
