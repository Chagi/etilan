#include <GLFW/glfw3.h>
#include "Maze.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

namespace{
	template<int Dim>
	void draw_cube(std::vector<PointVector<4>>& vec, double size, PointVector<4> position);
	
	void draw_cube(std::vector<PointVector<4>>& vec, PointVector<4> pts[8]){
		vec.push_back(pts[0]);
		vec.push_back(pts[1]);
		vec.push_back(pts[2]);
		vec.push_back(pts[3]);
		
		vec.push_back(pts[4]);
		vec.push_back(pts[5]);
		vec.push_back(pts[6]);
		vec.push_back(pts[7]);
		
		vec.push_back(pts[0]);
		vec.push_back(pts[4]);
		vec.push_back(pts[7]);
		vec.push_back(pts[3]);
		
		vec.push_back(pts[1]);
		vec.push_back(pts[5]);
		vec.push_back(pts[6]);
		vec.push_back(pts[2]);
		
		vec.push_back(pts[0]);
		vec.push_back(pts[1]);
		vec.push_back(pts[5]);
		vec.push_back(pts[4]);
		
		vec.push_back(pts[3]);
		vec.push_back(pts[2]);
		vec.push_back(pts[6]);
		vec.push_back(pts[7]);
	}
	
	template<>
	void draw_cube<3>(std::vector<PointVector<4>>& vec, double size, PointVector<4> position){
		size /= 2.0;
		double tmp_size = 0.2;
		PointVector<4> pts[] = {{position + PointVector<4>{-size,+size,-size,tmp_size}},
		                        {position + PointVector<4>{+size,+size,-size,tmp_size}},
		                        {position + PointVector<4>{+size,-size,-size,tmp_size}},
		                        {position + PointVector<4>{-size,-size,-size,tmp_size}},
		                        {position + PointVector<4>{-size,+size,+size,tmp_size}},
		                        {position + PointVector<4>{+size,+size,+size,tmp_size}},
		                        {position + PointVector<4>{+size,-size,+size,tmp_size}},
		                        {position + PointVector<4>{-size,-size,+size,tmp_size}}};
		
		draw_cube(vec, pts);
	}
	
	template<>
	void draw_cube<4>(std::vector<PointVector<4>>& vec, double size, PointVector<4> position){
		size /= 2.0;
		position += PointVector<4>{0,0,0,0.7};
		PointVector<4> pts1[] = {{position + PointVector<4>{-size,+size,-size,+size}},
		                         {position + PointVector<4>{+size,+size,-size,+size}},
		                         {position + PointVector<4>{+size,-size,-size,+size}},
		                         {position + PointVector<4>{-size,-size,-size,+size}},
		                         {position + PointVector<4>{-size,+size,+size,+size}},
		                         {position + PointVector<4>{+size,+size,+size,+size}},
		                         {position + PointVector<4>{+size,-size,+size,+size}},
		                         {position + PointVector<4>{-size,-size,+size,+size}}};
		
		PointVector<4> pts2[] = {{position + PointVector<4>{-size,+size,+size,-size}},
		                         {position + PointVector<4>{+size,+size,+size,-size}},
		                         {position + PointVector<4>{+size,-size,+size,-size}},
		                         {position + PointVector<4>{-size,-size,+size,-size}},
		                         {position + PointVector<4>{-size,+size,+size,+size}},
		                         {position + PointVector<4>{+size,+size,+size,+size}},
		                         {position + PointVector<4>{+size,-size,+size,+size}},
		                         {position + PointVector<4>{-size,-size,+size,+size}}};
		
		PointVector<4> pts3[] = {{position + PointVector<4>{-size,+size,-size,-size}},
		                         {position + PointVector<4>{+size,+size,-size,-size}},
		                         {position + PointVector<4>{+size,-size,-size,-size}},
		                         {position + PointVector<4>{-size,-size,-size,-size}},
		                         {position + PointVector<4>{-size,+size,-size,+size}},
		                         {position + PointVector<4>{+size,+size,-size,+size}},
		                         {position + PointVector<4>{+size,-size,-size,+size}},
		                         {position + PointVector<4>{-size,-size,-size,+size}}};
		
		PointVector<4> pts4[] = {{position + PointVector<4>{-size,+size,+size,-size}},
		                         {position + PointVector<4>{+size,+size,+size,-size}},
		                         {position + PointVector<4>{+size,+size,-size,-size}},
		                         {position + PointVector<4>{-size,+size,-size,-size}},
		                         {position + PointVector<4>{-size,+size,+size,+size}},
		                         {position + PointVector<4>{+size,+size,+size,+size}},
		                         {position + PointVector<4>{+size,+size,-size,+size}},
		                         {position + PointVector<4>{-size,+size,-size,+size}}};
		
		PointVector<4> pts5[] = {{position + PointVector<4>{-size,-size,+size,-size}},
		                         {position + PointVector<4>{+size,-size,+size,-size}},
		                         {position + PointVector<4>{+size,-size,-size,-size}},
		                         {position + PointVector<4>{-size,-size,-size,-size}},
		                         {position + PointVector<4>{-size,-size,+size,+size}},
		                         {position + PointVector<4>{+size,-size,+size,+size}},
		                         {position + PointVector<4>{+size,-size,-size,+size}},
		                         {position + PointVector<4>{-size,-size,-size,+size}}};
		
		PointVector<4> pts6[] = {{position + PointVector<4>{+size,+size,-size,-size}},
		                         {position + PointVector<4>{+size,+size,+size,-size}},
		                         {position + PointVector<4>{+size,-size,+size,-size}},
		                         {position + PointVector<4>{+size,-size,-size,-size}},
		                         {position + PointVector<4>{+size,+size,-size,+size}},
		                         {position + PointVector<4>{+size,+size,+size,+size}},
		                         {position + PointVector<4>{+size,-size,+size,+size}},
		                         {position + PointVector<4>{+size,-size,-size,+size}}};
		
		PointVector<4> pts7[] = {{position + PointVector<4>{-size,+size,-size,-size}},
		                         {position + PointVector<4>{-size,+size,+size,-size}},
		                         {position + PointVector<4>{-size,-size,+size,-size}},
		                         {position + PointVector<4>{-size,-size,-size,-size}},
		                         {position + PointVector<4>{-size,+size,-size,+size}},
		                         {position + PointVector<4>{-size,+size,+size,+size}},
		                         {position + PointVector<4>{-size,-size,+size,+size}},
		                         {position + PointVector<4>{-size,-size,-size,+size}}};
		
		PointVector<4> pts8[] = {{position + PointVector<4>{-size,+size,-size,-size}},
		                         {position + PointVector<4>{+size,+size,-size,-size}},
		                         {position + PointVector<4>{+size,-size,-size,-size}},
		                         {position + PointVector<4>{-size,-size,-size,-size}},
		                         {position + PointVector<4>{-size,+size,+size,-size}},
		                         {position + PointVector<4>{+size,+size,+size,-size}},
		                         {position + PointVector<4>{+size,-size,+size,-size}},
		                         {position + PointVector<4>{-size,-size,+size,-size}}};
		draw_cube(vec, pts1);
		draw_cube(vec, pts2);
		draw_cube(vec, pts3);
		draw_cube(vec, pts4);
		draw_cube(vec, pts5);
		draw_cube(vec, pts6);
		draw_cube(vec, pts7);
		draw_cube(vec, pts8);
	}
}

void draw_cube_4(std::vector<PointVector<4>>& vec, double size, PointVector<4> pos){
	draw_cube<4>(vec, size, pos);
}

void temp_cube(std::vector<PointVector<4>>& vec){
	draw_cube<4>(vec, 1, {0,0,0,0});
}


Maze::Maze(int /*dim*/, int nr){
	std::ifstream infile("mazes.txt");
	if(! infile.is_open())
		throw "";
	std::string maze;
	for(int i = 0; i < nr; i++)
		getline(infile, maze);
	PointVector<4> position{0,0,0,0};
	for(size_t i = 0; i < maze.size() + 3; i += 4){
		char d = maze[i];
		PointVector<4> dir{d=='x'?1.0:0.0,d=='y'?1.0:0.0,d=='z'?1.0:0.0,d=='w'?1.0:0.0};
		double s = (maze[i+1] == '+') ? 1.0 : -1.0;
		int l = maze[i+2] - 48;
		for(int i = 0; i < l+1; i++){
			draw_cube<4>(quads, 1.0, position);
			position += dir * s;
		}
	}
}

void Maze::move(PointVector<4> dir){
	for(auto& i : quads){
		i += dir;
	}
}

void Maze::rotate(int, int){
	
}

void Maze::draw(){
	glBegin(GL_QUADS);
	for(auto& i : quads){
		glVertex4dv((double *)&i);
	}
	glEnd();
}
