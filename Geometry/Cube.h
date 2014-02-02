/*
 * File: Cube.h
 * Author: Elias Forsberg
 *
 * Created on: February 1, 2014, 15:36
 */
 
#ifndef CUBE_H
#define CUBE_H

#include "PointVector.h"
#include "Face.h"

template<int Dim>
class Cube{};

template<>
class Cube<3> {
public:
	Cube(PointVector<4> position, double size);
	
private:
	Face<2> faces[6];
	
public:
	void draw();
	
};

template<>
class Cube<4> {
public:
	Cube(PointVector<4> position, double size);
	
private:
	Face<3> faces[8];

public:
	void draw();
	
};

#endif /* CUBE_H */

#include "Cube.hpp"
