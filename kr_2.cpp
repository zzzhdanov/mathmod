#include <stdio.h> 
#include <windows.h>
#include <gl/glut.h>
GLUnurbsObj* theNurb;
GLfloat ctlarray[11][2][4] = { {{-0.5, -0.3, -0.5,1.0},{-0.5, -0.3, 0.5,1.0}},
{{ -0.4, 0.3, -0.5,1.0},{-0.4, 0.3, 0.5,1.0}},
{{ -0.3, -0.3, -0.5,1.0},{-0.3, -0.3, 0.5,1.0}},
{{ -0.2, 0.3, -0.5,1.0},{-0.2, 0.3, 0.5,1.0}},
{{ -0.1, -0.3, -0.5,1.0},{ -0.1, -0.3, 0.5,1.0}},
{{0.0, 0.3, -0.5,1.0},{0.0, 0.3, 0.5, 1.0}},
{{0.1, -0.3, -0.5,1.0},{0.1, -0.3, 0.5,1.0}},
{{0.2, 0.3, -0.5,1.0},{0.2, 0.3, 0.5,1.0}},
{{0.3, -0.3, -0.5,1.0},{0.3, -0.3, 0.5,1.0}},
{{0.4, 0.3, -0.5,1.0},{0.4, 0.3, 0.5,1.0}},
{{0.5, -0.3, -0.5,1.0},{0.5, -0.3, 0.5,1.0}} };
GLfloat texpts[2][2][2] = { 0,0,0,1,1,0,1,1 };
GLUquadricObj* theqw; GLubyte* Iz_RGB;
void file_read() {
	FILE* stream;
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER InfoHeader;
	errno_t err = fopen_s(&stream, "test.bmp", "rb");
	fread(&FileHeader, sizeof(FileHeader), 1, stream);
	fread(&InfoHeader, sizeof(InfoHeader), 1, stream);
	fseek(stream, FileHeader.bfOffBits, SEEK_SET);
	int w = InfoHeader.biWidth;
	int h = InfoHeader.biHeight;
	Iz_RGB = (GLubyte*)malloc(w * h * 3);
	fread(Iz_RGB, w * h * 3, 1, stream);
	fclose(stream);
	for (int ii = 0; ii < w * h * 3; ii += 3) {
		GLubyte m1 = Iz_RGB[ii];
		Iz_RGB[ii] = Iz_RGB[ii + 2];
		Iz_RGB[ii + 2] = m1;
	}
}
void init() {
	glClearColor(0.1, 0.98, 0.3, 1);
	theNurb = gluNewNurbsRenderer();
	theqw = gluNewQuadric();
	glEnable(GL_DEPTH_TEST);
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, Iz_RGB);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	gluQuadricTexture(theqw, true);
	glEnable(GL_TEXTURE_2D);
	free(Iz_RGB);
}
void Display() {
	//GLfloat knot[] = { 0.0,0.0,0.0,0.1,0.2,0.3,0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0 };
	GLfloat knot[] = { 0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0 };
	GLfloat knot1[] = { 0.0,0.0,1.0,1.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(0.1, 1.0, -1.0, 1.0); glColor3f(1, 0, 0);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texpts[0][0][0]);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	//gluSphere(theqw, 0.3, 50, 50);
	gluBeginSurface(theNurb);
	gluNurbsSurface(theNurb, 10, knot, 4, knot1, 2 * 4, 4, &ctlarray[0][0][0], 3, 2, GL_MAP2_VERTEX_4);
	gluEndSurface(theNurb);
	glutPostRedisplay();
	glutSwapBuffers();
}
void main() {
	file_read();
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(480, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("  "); init(); glutDisplayFunc(Display); glutMainLoop();
}