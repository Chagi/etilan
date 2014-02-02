/*
 * File: Cube.hpp
 * Author: Elias Forsberg
 *
 * Created on: February 1, 2014, 15:36
 */
 
#ifndef CUBE_HPP
#define CUBE_HPP

Cube<3>::Cube(PointVector<4> pos, double size){
	size /= 2.0;
	faces[0] = Face<2>(pos + PointVector<4>{size,0,0,0}, {0,1,0,0}, {0,0,1,0});
	faces[1] = Face<2>(pos - PointVector<4>{size,0,0,0}, {0,1,0,0}, {0,0,1,0});
	faces[2] = Face<2>(pos + PointVector<4>{0,size,0,0}, {1,0,0,0}, {0,0,1,0});
	faces[3] = Face<2>(pos - PointVector<4>{0,size,0,0}, {1,0,0,0}, {0,0,1,0});
	faces[4] = Face<2>(pos + PointVector<4>{0,0,size,0}, {1,0,0,0}, {0,1,0,0});
	faces[5] = Face<2>(pos - PointVector<4>{0,0,size,0}, {1,0,0,0}, {0,1,0,0});
}

void Cube<3>::draw(){
	for(auto& f : faces){
		f.draw();
	}
}

Cube<4>::Cube(PointVector<4> pos, double size){
	size /= 2.0;
	faces[0] = Face<3>(pos + PointVector<4>{size,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1});
	faces[1] = Face<3>(pos - PointVector<4>{size,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1});
	faces[2] = Face<3>(pos + PointVector<4>{0,size,0,0}, {1,0,0,0}, {0,0,1,0}, {0,0,0,1});
	faces[3] = Face<3>(pos - PointVector<4>{0,size,0,0}, {1,0,0,0}, {0,0,1,0}, {0,0,0,1});
	faces[4] = Face<3>(pos + PointVector<4>{0,0,size,0}, {1,0,0,0}, {0,1,0,0}, {0,0,0,1});
	faces[5] = Face<3>(pos - PointVector<4>{0,0,size,0}, {1,0,0,0}, {0,1,0,0}, {0,0,0,1});
	faces[6] = Face<3>(pos + PointVector<4>{0,0,0,size}, {1,0,0,0}, {0,1,0,0}, {0,0,1,0});
	faces[7] = Face<3>(pos - PointVector<4>{0,0,0,size}, {1,0,0,0}, {0,1,0,0}, {0,0,1,0});
}

void Cube<4>::draw(){
	for(auto& f : faces){
		f.draw();
	}
}

#endif /* CUBE_H */
