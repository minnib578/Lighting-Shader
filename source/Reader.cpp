
#include "Reader.h"
#include <fstream>
#include <iostream>
#include"normal.h"

Reader::Reader(string filename)
{
	string line;
	fstream file;
	file.open(filename, ios::in);
	if (!file.is_open()) {
		cout << "Cannot open file" << endl;
	}
	while (!file.eof()) {
		getline(file, line);
		vector<string>attributes;
		string sep = "";
		line = line.append(" ");
		for (int i = 0; i < line.length(); i++) {
			if (line[i] != ' ') {
				sep += line[i];
			}
			else {
				attributes.push_back(sep);
				sep = "";
			}
		}

		if (attributes.size() != 4) {
			cout << "check size!!" << endl;
		}
		else {
			if (attributes[0] == "v") {
				vector<GLfloat>P;
				for (int i = 1; i < 4; i++) {
					P.push_back(atof(attributes[i].c_str()));
					vertexs.push_back(atof(attributes[i].c_str()));
				}
				Vertexs.push_back(P);
			}

			else if (attributes[0] == "f") {
				vector<GLint>vertex_index;
				for (int i = 1; i < 4; i++) {
					string x = attributes[i];
					string ans = "";
					for (int j = 0; j < (attributes[i]).length(); j++) {
						if (attributes[i][j] != '/') {
							ans += attributes[i][j];
						}
						else {
							break;
						}
					}
					GLint index = atof(ans.c_str());
					index = index--;
					vertex_index.push_back(index);
					indices.push_back(index);
				}
				Face.push_back(vertex_index);
			}
		}
	}
	file.close();

	float b_max = 0.0;
	float l;
	vector<vector<GLfloat>> V = Vertexs;
	for (int i = 0; i < V.size(); i++) {
		l = sqrt(pow(V[i][0], 2) + pow(V[i][1], 2) + pow(V[i][2], 2));
		if (l > b_max) {
			b_max = l;
		}
	}
	bounding = b_max * 3;
}

void Reader::Draw_LINE() {

	glBegin(GL_LINES);
	for (int i = 0; i < Face.size(); i++) {
		GLfloat n[3];                                             // normalize
		GLfloat V1[3];                                            // first vertex
		GLfloat V2[3];                                            // second vertex
		GLfloat V3[3];                                            // third vertex
		GLfloat vector1[3], vector2[3], vector3[3];               // three vectors of the plane
		GLfloat length;

		if ((Face[i]).size() != 3) {
			cout << "Check Face size!" << endl;
			break;
		}
		else {

			for (int j = 0; j < 3; j++) {
				V1[j] = (Vertexs[Face[i][0]])[j];
				V2[j] = (Vertexs[Face[i][1]])[j];
				V3[j] = (Vertexs[Face[i][2]])[j];
				vector1[j] = V1[j] - V2[j];
				vector2[j] = V1[j] - V3[j];
			}
			vector3[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
			vector3[1] = vector1[2] * vector2[0] - vector2[2] * vector1[0];
			vector3[2] = vector2[1] * vector1[0] - vector2[0] * vector1[1];
			length = sqrt(pow(vector3[0], 2) + pow(vector3[1], 2) + pow(vector3[2], 2));
			n[0] = vector3[0] / length;
			n[1] = vector3[1] / length;
			n[2] = vector3[2] / length;

			glNormal3f(n[0], n[1], n[2]);
			glVertex3f(V1[0], V1[1], V1[2]);
			glVertex3f(V2[0], V2[1], V2[2]);

			glVertex3f(V2[0], V2[1], V2[2]);
			glVertex3f(V3[0], V3[1], V3[2]);

			glVertex3f(V3[0], V3[1], V3[2]);
			glVertex3f(V1[0], V1[1], V1[2]);
		}
	}
	glEnd();

}

void Reader::Draw_POINT() {

	glBegin(GL_POINTS);
	for (int i = 0; i < Face.size(); i++) {
		GLfloat n[3];                                             // normalize
		GLfloat V1[3];                                            // first vertex
		GLfloat V2[3];                                            // second vertex
		GLfloat V3[3];                                            // third vertex
		GLfloat vector1[3], vector2[3], vector3[3];               // three vectors of the plane
		GLfloat length;

		if ((Face[i]).size() != 3) {
			cout << "Check Face size!" << endl;
			break;
		}
		else {

			for (int j = 0; j < 3; j++) {
				V1[j] = (Vertexs[Face[i][0]])[j];
				V2[j] = (Vertexs[Face[i][1]])[j];
				V3[j] = (Vertexs[Face[i][2]])[j];
				vector1[j] = V1[j] - V2[j];
				vector2[j] = V1[j] - V3[j];
			}
			vector3[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
			vector3[1] = vector1[2] * vector2[0] - vector2[2] * vector1[0];
			vector3[2] = vector2[1] * vector1[0] - vector2[0] * vector1[1];
			length = sqrt(pow(vector3[0], 2) + pow(vector3[1], 2) + pow(vector3[2], 2));
			n[0] = vector3[0] / length;
			n[1] = vector3[1] / length;
			n[2] = vector3[2] / length;
			glNormal3f(n[0], n[1], n[2]);
			glVertex3f(V1[0], V1[1], V1[2]);
			glVertex3f(V2[0], V2[1], V2[2]);
			glVertex3f(V3[0], V3[1], V3[2]);
		}
	}
	glEnd();
}

void Reader::Draw_TRIANGLE() {

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < Face.size(); i++) {
		GLfloat n[3];                                             // normalize
		GLfloat V1[3];                                            // first vertex
		GLfloat V2[3];                                            // second vertex
		GLfloat V3[3];                                            // third vertex
		GLfloat vector1[3], vector2[3], vector3[3];               // three vectors of the plane
		GLfloat length;

		if ((Face[i]).size() != 3) {
			cout << "Check Face size!" << endl;
			break;
		}
		else {

			for (int j = 0; j < 3; j++) {
				V1[j] = (Vertexs[Face[i][0]])[j];
				V2[j] = (Vertexs[Face[i][1]])[j];
				V3[j] = (Vertexs[Face[i][2]])[j];
				vector1[j] = V1[j] - V2[j];
				vector2[j] = V1[j] - V3[j];
			}
			vector3[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
			vector3[1] = vector1[2] * vector2[0] - vector2[2] * vector1[0];
			vector3[2] = vector2[1] * vector1[0] - vector2[0] * vector1[1];
			length = sqrt(pow(vector3[0], 2) + pow(vector3[1], 2) + pow(vector3[2], 2));
			n[0] = vector3[0] / length;
			n[1] = vector3[1] / length;
			n[2] = vector3[2] / length;
			glNormal3f(n[0], n[1], n[2]);
			glVertex3f(V1[0], V1[1], V1[2]);
			glVertex3f(V2[0], V2[1], V2[2]);
			glVertex3f(V3[0], V3[1], V3[2]);
		}
	}
	glEnd();
}

void Reader::Draw_TRIANGLE_Smooth() {

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < Face.size(); i++) {
		GLfloat n[3];                                             // normalize
		GLfloat V1[3];                                            // first vertex
		GLfloat V2[3];                                            // second vertex
		GLfloat V3[3];                                            // third vertex
		GLfloat vector1[3], vector2[3], vector3[3];               // three vectors of the plane
		GLfloat length;

		if ((Face[i]).size() != 3) {
			cout << "Check Face size!" << endl;
			break;
		}
		else {

			for (int j = 0; j < 3; j++) {
				V1[j] = (Vertexs[Face[i][0]])[j];
				V2[j] = (Vertexs[Face[i][1]])[j];
				V3[j] = (Vertexs[Face[i][2]])[j];
				vector1[j] = V1[j] - V2[j];
				vector2[j] = V1[j] - V3[j];
			}
			vector3[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
			vector3[1] = vector1[2] * vector2[0] - vector2[2] * vector1[0];
			vector3[2] = vector2[1] * vector1[0] - vector2[0] * vector1[1];
			length = sqrt(pow(vector3[0], 2) + pow(vector3[1], 2) + pow(vector3[2], 2));
			n[0] = vector3[0] / length;
			n[1] = vector3[1] / length;
			n[2] = vector3[2] / length;

			if (Vertexs.size() < 6000) {
				glNormal3f(normal_cactus[Face[i][0] * 3], normal_cactus[Face[i][0] * 3 + 1], normal_cactus[Face[i][0] * 3 + 2]);
				glVertex3f(V1[0], V1[1], V1[2]);
				glNormal3f(normal_cactus[Face[i][1] * 3], normal_cactus[Face[i][1] * 3 + 1], normal_cactus[Face[i][1] * 3 + 2]);
				glVertex3f(V2[0], V2[1], V2[2]);
				glNormal3f(normal_cactus[Face[i][2] * 3], normal_cactus[Face[i][2] * 3 + 1], normal_cactus[Face[i][2] * 3 + 2]);
				glVertex3f(V3[0], V3[1], V3[2]);
			}
			else {
				glNormal3f(normal_bunny[Face[i][0] * 3], normal_bunny[Face[i][0] * 3 + 1], normal_bunny[Face[i][0] * 3 + 2]);
				glVertex3f(V1[0], V1[1], V1[2]);
				glNormal3f(normal_bunny[Face[i][1] * 3], normal_bunny[Face[i][1] * 3 + 1], normal_bunny[Face[i][1] * 3 + 2]);
				glVertex3f(V2[0], V2[1], V2[2]);
				glNormal3f(normal_bunny[Face[i][2] * 3], normal_bunny[Face[i][2] * 3 + 1], normal_bunny[Face[i][2] * 3 + 2]);
				glVertex3f(V3[0], V3[1], V3[2]);
			}
		}
	}
	glEnd();
}
