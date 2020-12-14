#ifndef MATH_HELPER
#define MATH_HELPER

#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

class MathHelper {
public:
	// This is a column-order matrix multiply of matrices m1 and m2.
	static void matrixMult4x4(GLfloat* result, GLfloat* m1, GLfloat* m2);
	static void matrixMult4x4Column(GLfloat* result, GLfloat* m1, GLfloat* m2);
	// Makes an identity matrix
	static void makeIdentity(GLfloat* result);
	static void makeZero(GLfloat* result);
	// Returns a matrix that translates by x, y and z amount
	static void makeTranslate(GLfloat* result, GLfloat x, GLfloat y, GLfloat z);
	// Updates result to include a translate
	static void translateMatrixBy(GLfloat* result, GLfloat x, GLfloat y, GLfloat z);
	static void OC_Translate(GLfloat* result, GLfloat x, GLfloat y, GLfloat z);

	// Returns matrices that rotate about the X, Y and Z axes by a rotation amount (radians)
	static void makeRotateWX(GLfloat* result, GLfloat rotation);
	static void makeRotateWY(GLfloat* result, GLfloat rotation);
	static void makeRotateWZ(GLfloat* result, GLfloat rotation);
	static void OriC_TranslateX(GLfloat* result1, GLfloat* result2, GLfloat step);
	static void OriC_TranslateY(GLfloat* result1, GLfloat* result2, GLfloat step);
	static void OriC_TranslateZ(GLfloat* result1, GLfloat* result2, GLfloat step);
	static void makeRotateCX(GLfloat* result, GLfloat* ori, GLfloat rotation);
	static void makeRotateCY(GLfloat* result, GLfloat* ori, GLfloat rotation);
	static void makeRotateCZ(GLfloat* result, GLfloat* ori, GLfloat rotation);

	// Returns a scaling matrix
	static void makeScale(GLfloat* result, GLfloat x, GLfloat y, GLfloat z);

	// Make a perspective camera
	static void makePerspectiveMatrix(GLfloat* result, GLfloat fov, GLfloat aspect, GLfloat nearPlane, GLfloat farPlane);

	// Copies the src matrix into the dest matrix
	static void copyMatrix(GLfloat* src, GLfloat* dest);
	static void print4x4Matrix(GLfloat* mat);

private:
};


#endif