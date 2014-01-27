/* 
 * File:   Shaders.h
 * Author: Elias Forsberg
 *
 * Created on May 15, 2013, 7:39 PM
 */

#ifndef SHADERS_H
#define	SHADERS_H

#include <string>

void InitARBShader();
GLuint InitGLSLShader();
std::string loadFile(std::string file);

#endif	/* SHADERS_H */
