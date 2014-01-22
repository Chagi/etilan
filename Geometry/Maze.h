/*
 * File: Maze.h
 * Author: Elias Forsberg
 *
 * Created on: January 19, 2014, 14:37
 */
 
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "PointVector.h"

enum Direction {
	w = 0, x = 1, y = 2, z = 3
};

class Maze{
public:
	Maze(int dim, int nr);
	
public:
	std::vector<PointVector<4>> quads;
	std::vector<Direction> valid_steps;
	
public:
	void move(PointVector<4> dir);
	void rotate(int axis, int dir);
	void draw();
};

void draw_cube_4(std::vector<PointVector<4>>& vec, double size, PointVector<4> pos);

#endif /* MAZE_H */
