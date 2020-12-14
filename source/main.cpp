#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream> 
#include <sstream>
#include"Reader.h"
#include <windows.h>
#include "utils.h"
#include"camera.h"
#include"MathHelper.h"
#include"normal.h"
using namespace std;


string filePath = "cactus.obj";                             
Reader Model = Reader(filePath);
string primitive = "TRIANGLE";                            
string colors = "W";                                        
Camera CAM;
bool reset_shader = true;
bool reset_fix = true;
bool stop = false;
float near_plane = 0.1;
float far_plane = 100.0;
int p_x = 1;
int p_y = 1;
float w = 500;
float h = 500;
float mouse_sensitivity = 600;
GLuint vsID, fsID, pID, VBO, VAO, EBO;
GLfloat projectionMat[16], modelViewMat[16];
GLfloat red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat random[4] = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1 };
GLfloat* transMatrix;
GLfloat* M;        
GLfloat* V;				
GLfloat* P;				
GLfloat* Ori_C;

//parameters for HW3
int n_vertexs = Model.vertexs.size();
int n_indices = Model.indices.size();
int  light_switch = 1;
int shader = 1;

GLfloat ambient[4] = { 0.1,0.1,0.1, 1.0 };
GLfloat diffuse[4] = { 0.5,0.5, 0.5, 1.0 };
GLfloat specular[4] = { 0.5,0.5, 0.5, 1.0 };
GLfloat position[4] = { 5.0, 10.0, 6.0, 1.0 };
GLfloat Global_amb[4] = { 0.1,0.1, 0.1, 1.0 };

void Matrices_init() {
	
	transMatrix = new GLfloat[16];	MathHelper::makeIdentity(transMatrix);
	M = new GLfloat[16];			MathHelper::makeIdentity(M);
	V = new GLfloat[16];			MathHelper::makeIdentity(V);
	P = new GLfloat[16];			MathHelper::makeIdentity(P);
	Ori_C = new GLfloat[3];			MathHelper::makeZero(Ori_C);
}

void READ_MODEL() {
	string path = New_path();                                 	// get new file path 
	Model = Reader(path);
	n_vertexs = Model.vertexs.size();
	n_indices = Model.indices.size();
}

void RGBA_change() {

	float number;
	string command;
	cout << "please enter the light type you want to change:" << endl;
	getline(cin, command);

	if (command == "gam") {

		cout << "R: ";
		cin >> number;
		Global_amb[0] = number;
		cout << "G: ";
		cin >> number;
		Global_amb[1] = number;
		cout << "B: ";
		cin >> number;
		Global_amb[2] = number;
		cout << "A: ";
		cin >> number;
		Global_amb[3] = number;
		cout << "Global_amb: " << Global_amb[0] << " , " << Global_amb[1] << "  , " << Global_amb[2] << "  , " << Global_amb[3] << endl;
	}
	if (command == "am") {

		cout << "R: ";
		cin >> number;
		ambient[0] = number;
		cout << "G: ";
		cin >> number;
		ambient[1] = number;
		cout << "B: ";
		cin >> number;
		ambient[2] = number;
		cout << "A: ";
		cin >> number;
		ambient[3] = number;
		cout << "am: " << ambient[0] << " , " << ambient[1] << "  , " << ambient[2] << "  , " << ambient[3] << endl;
	}
	if (command == "df") {

		cout << "R: ";
		cin >> number;
		diffuse[0] = number;
		cout << "G: ";
		cin >> number;
		diffuse[1] = number;
		cout << "B: ";
		cin >> number;
		diffuse[2] = number;
		cout << "A: ";
		cin >> number;
		diffuse[3] = number;
		cout << "df: " << diffuse[0] << " , " << diffuse[1] << "  , " << diffuse[2] << "  , " << diffuse[3] << endl;
	}
	if (command == "sp") {

		cout << "R: ";
		cin >> number;
		specular[0] = number;
		cout << "G: ";
		cin >> number;
		specular[1] = number;
		cout << "B: ";
		cin >> number;
		specular[2] = number;
		cout << "A: ";
		cin >> number;
		specular[3] = number;
		cout << "sp: " << specular[0] << " , " << specular[1] << "  , " << specular[2] << "  , " << specular[3] << endl;
	}
}

void Init() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutCreateWindow("OpenGL");
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void readShaderFile(const GLchar* shaderPath, std::string& shaderCode)
{

	std::ifstream shaderFile;

	// ensures ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;

		// Read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();

		// close file handlers
		shaderFile.close();

		// Convert stream into GLchar array
		shaderCode = shaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

}

void Buffer()
{
	
	n_vertexs = Model.vertexs.size();
	n_indices = Model.indices.size();
	GLfloat* vertData = new GLfloat[n_vertexs];
	GLint* indices = new GLint[n_indices];

	for (int i = 0; i < n_vertexs; i++) {
		vertData[i] = Model.vertexs[i];
	}
	for (int i = 0; i < n_indices; i++) {
		indices[i] = Model.indices[i];
	}
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 2 * Model.vertexs.size() * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, Model.vertexs.size() * sizeof(GLfloat), vertData);


	glBufferData(GL_ARRAY_BUFFER, 2 * Model.vertexs.size() * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, Model.vertexs.size() * sizeof(GLfloat), vertData);

	if (Model.vertexs.size() > 6000) {

		glBufferSubData(GL_ARRAY_BUFFER, Model.vertexs.size() * sizeof(GLfloat), Model.vertexs.size() * sizeof(GLfloat), normal_bunny);
	}
	else {

		glBufferSubData(GL_ARRAY_BUFFER, Model.vertexs.size() * sizeof(GLfloat), Model.vertexs.size() * sizeof(GLfloat), normal_cactus);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Model.indices.size() * sizeof(GLint), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(Model.vertexs.size() * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}

void Shader() {
	char* vs = NULL, * fs = NULL;

	std::string vertShaderString;
	std::string fragShaderString;

	//create shader
	vsID = glCreateShader(GL_VERTEX_SHADER);
	fsID = glCreateShader(GL_FRAGMENT_SHADER);

	//read shader source
	readShaderFile("vertexshader.txt", vertShaderString);
	readShaderFile("fragshader.txt", fragShaderString);

	const GLchar* pVertShaderSource = vertShaderString.c_str();
	const GLchar* pFragShaderSource = fragShaderString.c_str();

	//connect shader and source code
	glShaderSource(vsID, 1, &pVertShaderSource, NULL);
	glShaderSource(fsID, 1, &pFragShaderSource, NULL);

	//compile shader
	glCompileShader(vsID);
	glCompileShader(fsID);

	//create program
	pID = glCreateProgram();
	glAttachShader(pID, vsID);
	glAttachShader(pID, fsID);

	//link program
	glLinkProgram(pID);

	//use program
	glUseProgram(pID);
}

void MyReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	w = width;
	h = height;
}

void myIdlex()
{
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q') exit(0);
	if (key == '0') { 
		Model = Reader("bunny.obj"); 
		Buffer(); }
	if (key == '1') { 
		Model = Reader("cactus.obj");
		Buffer(); }


	if (key == 'r') { reset_shader = true; reset_fix = true; }
	if (key == '2') { READ_MODEL(); Buffer(); reset_shader = true; reset_fix = true; }

	if (key == '3') { primitive = "POINT"; }
	else if (key == '4') { primitive = "LINE"; }
	else if (key == '5') { primitive = "TRIANGLE"; }



	if (key == '6') { colors = "R"; }
	if (key == '7') { colors = "G"; }
	if (key == '8') { colors = "B"; }
	if (key == '9') { colors = "W"; }
	if (key == 'c') {
		random[0] = (float)rand() / RAND_MAX;
		random[1] = (float)rand() / RAND_MAX;
		random[2] = (float)rand() / RAND_MAX;
		random[3] = (float)rand() / RAND_MAX;
		colors = "Random";
	}


	float scale = Model.bounding / 1.5;
	if (key == 'w' || key == 'W') {
		CAM.F_B(scale * -0.1f);
		MathHelper::OriC_TranslateZ(Ori_C, V, scale * -0.1f);
	}
	if (key == 'z' || key == 'Z') {
		CAM.F_B(scale * 0.1f);
		MathHelper::OriC_TranslateZ(Ori_C, V, scale * 0.1f);
	}
	if (key == 'a' || key == 'A') {
		CAM.R_L(scale * 0.1f);     
		MathHelper::OriC_TranslateX(Ori_C, V, scale * -0.1f);
	}
	if (key == 's' || key == 'S') {
		CAM.R_L(scale * -0.1f);    
		MathHelper::OriC_TranslateX(Ori_C, V, scale * 0.1f);
	}
	if (key == 'u' || key == 'U') {
		CAM.U_D(scale * 0.1f);
		MathHelper::OriC_TranslateY(Ori_C, V, scale * -0.1f);
	}
	if (key == 'd' || key == 'D') {
		CAM.U_D(scale * -0.1f);        
		MathHelper::OriC_TranslateY(Ori_C, V, scale * 0.1f);
	}


	if (key == 'n') {
		near_plane += scale * 0.1;

	}
	if (key == 'N') {
		near_plane -= scale * 0.1;
		if (near_plane <= 0.1) near_plane = 0.1;

	}
	if (key == 'f') {
		far_plane += scale * 0.1;

	}
	if (key == 'F') {
		far_plane -= scale * 0.1;
		if (far_plane <= 0.1) far_plane = 0.1;

	}

	if (key == 'l' || key == 'L')
	{
		if (light_switch != 1) {
			light_switch = 1;
		}

		else {
			light_switch = 0;
		}

	}
	if (key == 'p' || key == 'P')
	{
		if (shader == 1) {
			shader =0;
			cout << "Flat  Shading" << endl;
		}

		else {
			shader = 1;
			cout << "Smoothing Shading" << endl;
		}
	}
	if (key == 'g' || key == 'G')
	{   
		RGBA_change();
	}

	if (key == ' ') stop = !stop;
	if (stop)
		glutIdleFunc(NULL);
	else
		glutIdleFunc(myIdlex);
}

void MouseWheel(int wheel, int direction, int x, int y)
{
	float scale = Model.bounding;
	wheel = 0;
	if (direction == -1) {
		CAM.F_B(scale * 0.2f);
		MathHelper::OriC_TranslateZ(Ori_C, V, scale * 0.2f);
	}
	else if (direction == +1) {
		CAM.F_B(scale * -0.2f);
		MathHelper::OriC_TranslateZ(Ori_C, V, scale * -0.2f);
	}
	glutIdleFunc(myIdlex);
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_LEFT_BUTTON) {
		p_x = x; p_y = y;
	}
}

void ViewPoint(int x, int y)
{
	float dx = x - p_x;
	float dy = y - p_y;
	CAM.Y_axis(-dx / mouse_sensitivity);
	CAM.X_axis(-dy / mouse_sensitivity);
	MathHelper::makeRotateCX(V, Ori_C, -dy / mouse_sensitivity);
	MathHelper::makeRotateCY(V, Ori_C, -dx / mouse_sensitivity);
	p_x = x;
	p_y = y;
}

void light_material() {

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Global_amb);
	if (light_switch==1) {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	glEnable(GL_COLOR_MATERIAL);
	GLfloat shine[] = { 40.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Global_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);

}

void display_fixed_pipeline()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	light_material();
	if (colors == "R") { glColor3f(1.0, 0.0, 0.0); }                                      // change model rendering color
	else if (colors == "G") { glColor3f(0.0, 1.0, 0.0); }
	else if (colors == "B") { glColor3f(0.0, 0.0, 01.0); }
	else if (colors == "W") { glColor3f(1.0, 1.0, 1.0); }
	else if (colors == "Random") { glColor3f(random[0], random[1], random[2]); }
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float scale = Model.bounding / 1.5;                                                      // choose propertive camera coordinate according to the new model dimension
	if (reset_fix == true) {                                                   // reset the camera to original point when change file and reset 
		CAM.eye = vector3f(scale, 0, scale);
		CAM.at = vector3f(-1, 0, -1);
		CAM.up = vector3f(0, 1, 0);
		near_plane = 0.1;
		far_plane = 50;
		reset_fix = false;
	}

	gluLookAt(CAM.eye.x, CAM.eye.y, CAM.eye.z,
		CAM.eye.x + CAM.at.x,
		CAM.eye.y + CAM.at.y,
		CAM.eye.z + CAM.at.z,
		CAM.up.x, CAM.up.y, CAM.up.z);

	if (primitive == "POINT") {                                                      // rendering the object using different kinds of primitives
		Model.Draw_POINT();
	}
	else if (primitive == "LINE") {
		Model.Draw_LINE();
	}
	else {
		if (shader==1) {
			glShadeModel(GL_SMOOTH);
			Model.Draw_TRIANGLE_Smooth();
		}
		else if (shader!=1) {
			glShadeModel(GL_FLAT);
			Model.Draw_TRIANGLE();
		}
	}
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glFlush();
	glutSwapBuffers();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLdouble)w / (GLdouble)h, (GLdouble)near_plane, (GLdouble)far_plane);
	glMatrixMode(GL_MODELVIEW);
}

void display_shader(void)
{   

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(pID);
	float scale = Model.bounding/1.5;
	if (reset_shader == true) {
		MathHelper::makeIdentity(V);
		MathHelper::makeZero(Ori_C);
		MathHelper::OC_Translate(Ori_C, -scale, 0.0f, -scale);
		MathHelper::makeTranslate(V, -scale, 0.0f, -scale);
		MathHelper::makeRotateCY(V, Ori_C, 3.1415926/4);
		near_plane = 0.1;
		far_plane = 100;
		reset_shader = false;
	}
	MathHelper::makeRotateCX(V, Ori_C, 0);
	MathHelper::makePerspectiveMatrix(P, 60.0f, w / h, near_plane, far_plane);


	//parameters ID
	GLuint modeViewMatLocation = glGetUniformLocation(pID, "modelviewMatrix");
	GLuint projectionMatLocation = glGetUniformLocation(pID, "projectionMatrix");
	GLuint transformMatLocation = glGetUniformLocation(pID, "transformationMatrix");
	GLuint colorID = glGetUniformLocation(pID, "objectcolor");
	GLuint glb_am_ID = glGetUniformLocation(pID, "Global_amb");
	GLuint am_ID = glGetUniformLocation(pID, "ambient");
	GLuint df_ID = glGetUniformLocation(pID, "df");
	GLuint sp_ID = glGetUniformLocation(pID, "sp");
	GLuint lightps_ID = glGetUniformLocation(pID, "lightpos");
	GLuint viewpos_ID = glGetUniformLocation(pID, "viewpos");
	GLuint light_shader_ID = glGetUniformLocation(pID, "light_switch");
	GLuint shader_model_ID = glGetUniformLocation(pID, "shader_model");
	
	//parameters for shader
	glUniform4fv(glb_am_ID, 1, Global_amb);
	glUniform4fv(am_ID, 1, ambient);
	glUniform4fv(df_ID, 1, diffuse);
	glUniform4fv(sp_ID, 1, specular);
	glUniform4fv(lightps_ID, 1, position);
	glUniform1i(light_shader_ID, light_switch);
	glUniform1i(shader_model_ID, shader);
	glUniform3fv(viewpos_ID, 1, Ori_C);
	glUniformMatrix4fv(modeViewMatLocation, 1, GL_TRUE, V);
	glUniformMatrix4fv(projectionMatLocation, 1, GL_TRUE, P);
	if (colors == "R") {
		glUniform4fv(colorID, 1, red);
	}
	else if (colors == "G") {

		glUniform4fv(colorID, 1, green);
	}
	else if (colors == "B") {
		glUniform4fv(colorID, 1, blue);
	}
	else if (colors == "W") {
		glUniform4fv(colorID, 1, white);
	}
	else if(colors == "Random") {
		glUniform4fv(colorID, 1, random);
	}



	glDeleteShader(vsID);
	glDeleteShader(fsID);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(VAO);
	
	if (primitive == "POINT") {
		glDrawElements(GL_POINTS, 3*Model.vertexs.size(), GL_UNSIGNED_INT, 0);
	}
	else if (primitive == "LINE") {
		glDrawElements(GL_LINES, 3*Model.vertexs.size(), GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawElements(GL_TRIANGLES, 3*Model.vertexs.size(), GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
	glEnable(GL_CULL_FACE);                                                     
	glPolygonMode(GL_FRONT, GL_FILL);
	glFrontFace(GL_CCW);
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	Init();
	glutSetWindowTitle("Fixed");
	glutPositionWindow(1100, 250);
	glutReshapeFunc(MyReshape);
	glutDisplayFunc(display_fixed_pipeline);
	glutIdleFunc(myIdlex);
	glutMouseWheelFunc(MouseWheel);
	glutMouseFunc(Mouse);
	glutMotionFunc(ViewPoint);
	glutKeyboardFunc(keyboard);
	

	Init();
	glutSetWindowTitle("Shader");
	glutPositionWindow(500, 250);
	glewInit();
	Matrices_init();
	Buffer();
	Shader();
	glutReshapeFunc(MyReshape);
	glutDisplayFunc(display_shader);
	glutIdleFunc(myIdlex);
	glutMouseWheelFunc(MouseWheel);
	glutMouseFunc(Mouse);
	glutMotionFunc(ViewPoint);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;

}
