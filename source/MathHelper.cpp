#include "MathHelper.h"
#define T0 0
#define T1 4
#define T2 8
#define T3 12
#define T4 1
#define T5 5
#define T6 9
#define T7 13
#define T8 2
#define T9 6
#define T10 10
#define T11 14
#define T12 3
#define T13 7
#define T14 11
#define T15 15

// This is a column-order matrix multiply of matrices m1 and m2.
void MathHelper::matrixMult4x4Column(GLfloat* result, GLfloat* m1, GLfloat* m2)
{
	for (int i = 0; i < 16; i++) {
		result[i] = 0.0f;
	}
	result[T0] = m1[T0] * m2[T0] + m1[T1] * m2[T4] + m1[T2] * m2[T8] + m1[T3] * m2[T12];
	result[T1] = m1[T0] * m2[T1] + m1[T1] * m2[T5] + m1[T2] * m2[T9] + m1[T3] * m2[T13];
	result[T2] = m1[T0] * m2[T2] + m1[T1] * m2[T6] + m1[T2] * m2[T10] + m1[T3] * m2[T14];
	result[T3] = m1[T0] * m2[T3] + m1[T1] * m2[T7] + m1[T2] * m2[T11] + m1[T3] * m2[T15];

	result[T4] = m1[T4] * m2[T0] + m1[T5] * m2[T4] + m1[T6] * m2[T8] + m1[T7] * m2[T12];
	result[T5] = m1[T4] * m2[T1] + m1[T5] * m2[T5] + m1[T6] * m2[T9] + m1[T7] * m2[T13];
	result[T6] = m1[T4] * m2[T2] + m1[T5] * m2[T6] + m1[T6] * m2[T10] + m1[T7] * m2[T14];
	result[T7] = m1[T4] * m2[T3] + m1[T5] * m2[T7] + m1[T6] * m2[T11] + m1[T7] * m2[T15];

	result[T8] = m1[T8] * m2[T0] + m1[T9] * m2[T4] + m1[T10] * m2[T8] + m1[T11] * m2[T12];
	result[T9] = m1[T8] * m2[T1] + m1[T9] * m2[T5] + m1[T10] * m2[T9] + m1[T11] * m2[T13];
	result[T10] = m1[T8] * m2[T2] + m1[T9] * m2[T6] + m1[T10] * m2[T10] + m1[T11] * m2[T14];
	result[T11] = m1[T8] * m2[T3] + m1[T9] * m2[T7] + m1[T10] * m2[T11] + m1[T11] * m2[T15];

	result[T12] = m1[T12] * m2[T0] + m1[T13] * m2[T4] + m1[T14] * m2[T8] + m1[T15] * m2[T12];
	result[T13] = m1[T12] * m2[T1] + m1[T13] * m2[T5] + m1[T14] * m2[T9] + m1[T15] * m2[T13];
	result[T14] = m1[T12] * m2[T2] + m1[T13] * m2[T6] + m1[T14] * m2[T10] + m1[T15] * m2[T14];
	result[T15] = m1[T12] * m2[T3] + m1[T13] * m2[T7] + m1[T14] * m2[T11] + m1[T15] * m2[T15];
}
void MathHelper::matrixMult4x4(GLfloat* result, GLfloat* m1, GLfloat* m2)
{
	for (int i = 0; i < 16; i++) {
		result[i] = 0.0f;
	}
	result[0] = m1[0] * m2[0] + m1[1] * m2[4] + m1[2] * m2[8] + m1[3] * m2[12];
	result[1] = m1[0] * m2[1] + m1[1] * m2[5] + m1[2] * m2[9] + m1[3] * m2[13];
	result[2] = m1[0] * m2[2] + m1[1] * m2[6] + m1[2] * m2[10] + m1[3] * m2[14];
	result[3] = m1[0] * m2[3] + m1[1] * m2[7] + m1[2] * m2[11] + m1[3] * m2[15];

	result[4] = m1[4] * m2[0] + m1[5] * m2[4] + m1[6] * m2[8] + m1[7] * m2[12];
	result[5] = m1[4] * m2[1] + m1[5] * m2[5] + m1[6] * m2[9] + m1[7] * m2[13];
	result[6] = m1[4] * m2[2] + m1[5] * m2[6] + m1[6] * m2[10] + m1[7] * m2[14];
	result[7] = m1[4] * m2[3] + m1[5] * m2[7] + m1[6] * m2[11] + m1[7] * m2[15];

	result[8] = m1[8] * m2[0] + m1[9] * m2[4] + m1[10] * m2[8] + m1[11] * m2[12];
	result[9] = m1[8] * m2[1] + m1[9] * m2[5] + m1[10] * m2[9] + m1[11] * m2[13];
	result[10] = m1[8] * m2[2] + m1[9] * m2[6] + m1[10] * m2[10] + m1[11] * m2[14];
	result[11] = m1[8] * m2[3] + m1[9] * m2[7] + m1[10] * m2[11] + m1[11] * m2[15];

	result[12] = m1[12] * m2[0] + m1[13] * m2[4] + m1[14] * m2[8] + m1[15] * m2[12];
	result[13] = m1[12] * m2[1] + m1[13] * m2[5] + m1[14] * m2[9] + m1[15] * m2[13];
	result[14] = m1[12] * m2[2] + m1[13] * m2[6] + m1[14] * m2[10] + m1[15] * m2[14];
	result[15] = m1[12] * m2[3] + m1[13] * m2[7] + m1[14] * m2[11] + m1[15] * m2[15];
}

// Makes an identity matrix
void MathHelper::makeIdentity(GLfloat* result)
{
	for (int i = 0; i < 16; i++) {
		result[i] = 0.0f;
	}
	result[0] = result[5] = result[10] = result[15] = 1.0f;
}

void MathHelper::makeZero(GLfloat* result)
{
	for (int i = 0; i < 3; i++) {
		result[i] = 0.0f;
	}
}

// Returns a matrix that translates by x, y and z amount
void MathHelper::makeTranslate(GLfloat* result, GLfloat x, GLfloat y, GLfloat z)
{
	makeIdentity(result);
	result[3] = x;
	result[7] = y;
	result[11] = z;
}
void MathHelper::OC_Translate(GLfloat* result, GLfloat x, GLfloat y, GLfloat z)
{
	result[0] += x;
	result[1] += y;
	result[2] += z;
}
// Returns matrices that rotate about the X, Y and Z axes by a rotation amount (radians)
void MathHelper::makeRotateWX(GLfloat* result, GLfloat rotation)
{
	makeIdentity(result);
	result[5] = result[10] = cos(rotation);
	result[6] = sin(rotation);
	result[9] = -result[6];
}
void MathHelper::makeRotateWY(GLfloat* result, GLfloat rotation)
{
	makeIdentity(result);
	result[0] = result[10] = cos(rotation);
	result[2] = -sin(rotation);
	result[8] = -result[2];
}
void MathHelper::makeRotateWZ(GLfloat* result, GLfloat rotation)
{
	makeIdentity(result);
	result[0] = result[5] = cos(rotation);
	result[1] = sin(rotation);
	result[4] = -result[1];
}

// Returns a matrix that translates by u, v and n amount
void MathHelper::OriC_TranslateX(GLfloat* result1, GLfloat* result2, GLfloat step)
{
	result1[0] += result2[T0] * step;
	result1[1] += result2[T4] * step;
	result1[2] += result2[T8] * step;
}
void MathHelper::OriC_TranslateY(GLfloat* result1, GLfloat* result2, GLfloat step)
{
	result1[0] += result2[T1] * step;
	result1[1] += result2[T5] * step;
	result1[2] += result2[T9] * step;
}
void MathHelper::OriC_TranslateZ(GLfloat* result1, GLfloat* result2, GLfloat step)
{
	result1[0] += result2[T2] * step;
	result1[1] += result2[T6] * step;
	result1[2] += result2[T10] * step;
}

//Returns matrices that rotate about the u, v and n axes by a rotation amount (radians)
void MathHelper::makeRotateCX(GLfloat* result, GLfloat* ori, GLfloat rotation)
{
	float cosa = cos(rotation), sina = sin(rotation);
	GLfloat* VM;
	VM = new GLfloat[16];
	MathHelper::copyMatrix(result, VM);
	float ux = VM[T0], uy = VM[T4], uz = VM[T8];
	result[T1] = (ux * ux * (1 - cosa) + cosa) * VM[T1] + (ux * uy * (1 - cosa) - sina * uz) * VM[T5] + (ux * uz * (1 - cosa) + sina * uy) * VM[T9];
	result[T5] = (ux * uy * (1 - cosa) + sina * uz) * VM[T1] + (uy * uy * (1 - cosa) + cosa) * VM[T5] + (uy * uz * (1 - cosa) - sina * ux) * VM[T9];
	result[T9] = (ux * uz * (1 - cosa) - sina * uy) * VM[T1] + (uy * uz * (1 - cosa) + sina * ux) * VM[5] + (uz * uz * (1 - cosa) + cosa) * VM[T9];
	result[T2] = (ux * ux * (1 - cosa) + cosa) * VM[T2] + (ux * uy * (1 - cosa) - sina * uz) * VM[T6] + (ux * uz * (1 - cosa) + sina * uy) * VM[T10];
	result[T6] = (ux * uy * (1 - cosa) + sina * uz) * VM[T2] + (uy * uy * (1 - cosa) + cosa) * VM[T6] + (uy * uz * (1 - cosa) - sina * ux) * VM[T10];
	result[T10] = (ux * uz * (1 - cosa) - sina * uy) * VM[T2] + (uy * uz * (1 - cosa) + sina * ux) * VM[T6] + (uz * uz * (1 - cosa) + cosa) * VM[T10];
	result[T12] = result[T0] * ori[0] + result[T4] * ori[1] + result[T8] * ori[2];
	result[T13] = result[T1] * ori[0] + result[T5] * ori[1] + result[T9] * ori[2];
	result[T14] = result[T2] * ori[0] + result[T6] * ori[1] + result[T10] * ori[2];
}

void MathHelper::makeRotateCY(GLfloat* result, GLfloat* ori, GLfloat rotation)
{
	float cosa = cos(rotation), sina = sin(rotation);
	GLfloat* VM;
	VM = new GLfloat[16];
	MathHelper::copyMatrix(result, VM);
	//float ux = VM[T1], uy = VM[T5], uz = VM[T9];
	float ux = 0, uy = 1, uz = 0;
	result[T0] = (ux * ux * (1 - cosa) + cosa) * VM[T0] + (ux * uy * (1 - cosa) - sina * uz) * VM[T4] + (ux * uz * (1 - cosa) + sina * uy) * VM[T8];
	result[T4] = (ux * uy * (1 - cosa) + sina * uz) * VM[T0] + (uy * uy * (1 - cosa) + cosa) * VM[T4] + (uy * uz * (1 - cosa) - sina * ux) * VM[T8];
	result[T8] = (ux * uz * (1 - cosa) - sina * uy) * VM[T0] + (uy * uz * (1 - cosa) + sina * ux) * VM[5] + (uz * uz * (1 - cosa) + cosa) * VM[T8];
	result[T2] = (ux * ux * (1 - cosa) + cosa) * VM[T2] + (ux * uy * (1 - cosa) - sina * uz) * VM[T6] + (ux * uz * (1 - cosa) + sina * uy) * VM[T10];
	result[T6] = (ux * uy * (1 - cosa) + sina * uz) * VM[T2] + (uy * uy * (1 - cosa) + cosa) * VM[T6] + (uy * uz * (1 - cosa) - sina * ux) * VM[T10];
	result[T10] = (ux * uz * (1 - cosa) - sina * uy) * VM[T2] + (uy * uz * (1 - cosa) + sina * ux) * VM[T6] + (uz * uz * (1 - cosa) + cosa) * VM[T10];
	result[T12] = result[T0] * ori[0] + result[T4] * ori[1] + result[T8] * ori[2];
	result[T13] = result[T1] * ori[0] + result[T5] * ori[1] + result[T9] * ori[2];
	result[T14] = result[T2] * ori[0] + result[T6] * ori[1] + result[T10] * ori[2];
}

// 2) Create the makeScale method here and fill in the code using the examples above and below
void MathHelper::makeScale(GLfloat* result, GLfloat x, GLfloat y, GLfloat z)
{
	makeIdentity(result);
	result[0] = x;
	result[5] = y;
	result[10] = z;
}


void MathHelper::makePerspectiveMatrix(GLfloat* result, GLfloat fov, GLfloat aspect, GLfloat nearPlane, GLfloat farPlane) {
	GLfloat f = 1.0f / tan(fov * 3.1415926f / 360.0f);
	makeIdentity(result);
	result[T0] = f / aspect;
	result[T5] = f;
	result[T10] = ((farPlane + nearPlane) / (nearPlane - farPlane));
	result[T11] = -1;
	result[T14] = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);
	result[T15] = 0;
}

void MathHelper::translateMatrixBy(GLfloat* result, GLfloat x, GLfloat y, GLfloat z)
{
	result[3] += x;
	result[7] += y;
	result[11] += z;
}

void MathHelper::copyMatrix(GLfloat* src, GLfloat* dest)
{
	for (int i = 0; i < 16; i++) {
		dest[i] = src[i];
	}
}

void MathHelper::print4x4Matrix(GLfloat* mat)
{
	printf("====================================");
	for (int i = 0; i < 16; i++) {
		if (i % 4 == 0) printf("\n");
		printf("%f\t", mat[i]);
	}
	printf("\n");
}
