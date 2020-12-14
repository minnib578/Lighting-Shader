#pragma once
#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "vector3f.h"

struct Camera {
	vector3f eye;
	vector3f at;
	vector3f up;
	Camera() {
		eye = vector3f(0, 0, 0);
		at = vector3f(0, 0, -1);
		up = vector3f(0, 1, 0);
	}
	void F_B(GLfloat);
	void R_L(GLfloat);
	void U_D(GLfloat);
	void Y_axis(GLfloat);
	void X_axis(GLfloat);

};

#endif