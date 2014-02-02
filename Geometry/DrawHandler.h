/*
 * File: DrawHandler.h
 * Author: Elias Forsberg
 *
 * Created on: February 1, 2014, 16:12
 */
 
#ifndef DRAWHANDLER_H
#define DRAWHANDLER_H

#include "PointVector.h"

class DrawHandler{
public:
	DrawHandler();

private:
	double separation;
	PointVector<4> translation;
	
	double retina_size;
	PointVector<4> color;
	
	PointVector<4> eyepos;
	PointVector<4> lookat;

public:
	void reset();
	
	void separate(double sep);
	void translate(PointVector<4> pos);
	
	void drawQuad(PointVector<4> a, PointVector<4> b, PointVector<4> c, PointVector<4> d);
	void setColor(PointVector<4> c);
};

#endif /* DRAWHANDLER_CPP */
