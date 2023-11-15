#include <GL/glut.h> 
GLUnurbsObj* nobj; 
// массив точек определяющего многоугольника 
GLfloat ctlarray[][3] = { {-0.9, -0.8, 0.0},{-0.2, 0.8, 0.0},{-0.2, 0.8, 0.0},{-0.2, 0.8, 0.0},{0.2, -0.5, 0.0},{0.9, 0.8, 0.0} }; 
GLfloat ctlarray1[][3] = { {-0.9, -0.8, 0.0},{-0.2, 0.8, 0.0},{-0.2, 0.8, 0.0},{0.2, -0.5, 0.0},{0.9, 0.8, 0.0} }; 
GLfloat ctlarray2[][3] = { {-0.9, -0.8, 0.0},{-0.2, 0.8, 0.0},{0.2, -0.5, 0.0},{0.9, 0.8, 0.0} }; 
void init(void) 
{ 
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    //создается NURBS-объект 
    nobj = gluNewNurbsRenderer(); 
    // устанавливается свойство неравномерного рационального B-сплайна 
      //  GLU_SAMPLING_TOLERANCE – свойство – задает максимальную длину в пикселях 
      //  25.0 – значение свойства (используется при разбиении ) 
    gluNurbsProperty(nobj, GLU_SAMPLING_TOLERANCE, 25.0); 
} 
void Display() 
{ 
    // массив содержащий значения открытого равномерного узлового вектора  
    GLfloat knot[] = { 0,0,0,0,1,1,1,1 }; 
    GLfloat knot1[] = { 0,0,0,0,1,2,2,2,2 }; 
    GLfloat knot2[] = { 0,0,0,0,1,2,3,3,3,3 }; 
 
    glClear(GL_COLOR_BUFFER_BIT); 
    glLineWidth(3.0); 
    glColor3f(0.0, 0.3, 1.0); 
    //генерация и отображение NURBS кривой  
    gluNurbsCurve(nobj, 10, knot2, 3, &ctlarray[0][0], 4, GL_MAP1_VERTEX_3); 
    gluNurbsCurve(nobj, 9, knot1, 3, &ctlarray1[0][0], 4, GL_MAP1_VERTEX_3); 
    gluNurbsCurve(nobj, 8, knot, 3, &ctlarray2[0][0], 4, GL_MAP1_VERTEX_3); 
    glBegin(GL_POINTS); 
    for (int i = 0; i < 4; i++) { 
        glVertex3f(ctlarray[i][0], ctlarray[i][1], ctlarray[i][2]); 
    } 
    glEnd(); 
    glFlush(); 
} 
void Display1() 
{ 
    // массив содержащий значения открытого равномерного узлового вектора  
    GLfloat knot[] = { 0.0,0.0,1.0,2.0,3.0,3.0 }; 
    glClear(GL_COLOR_BUFFER_BIT); 
    glLineWidth(3.0); 
    glColor3f(0.0, 0.3, 1.0); 
    //генерация и отображение NURBS кривой  
    gluNurbsCurve(nobj, 6, knot, 3, &ctlarray[0][0], 2, GL_MAP1_VERTEX_3); 
    glPointSize(4.0); 
    glColor3f(0.0, 0.0, 1.0); 
    glBegin(GL_POINTS); 
    for (int i = 0; i < 4; i++) { 
        glVertex3f(ctlarray[i][0], ctlarray[i][1], ctlarray[i][2]); 
    } 
    glEnd(); 
    glFlush(); 
} 
void Display2() 
{ 
    // массив содержащий значения открытого равномерного узлового вектора  
    GLfloat knot[] = { 0.0,0.0,0.0, 0.0, 1.0, 1.0,1.0,1.0 }; 
    glClear(GL_COLOR_BUFFER_BIT); 
    glLineWidth(3.0); 
    glColor3f(0.0, 0.3, 1.0); 
    //генерация и отображение NURBS кривой  
    gluNurbsCurve(nobj, 8, knot, 3, &ctlarray[0][0], 4, GL_MAP1_VERTEX_3); 
    glPointSize(4.0); 
    glColor3f(0.0, 0.0, 1.0); 
    glBegin(GL_POINTS); 
    for (int i = 0; i < 4; i++) { 
        glVertex3f(ctlarray[i][0], ctlarray[i][1], ctlarray[i][2]); 
    } 
    glEnd(); 
    glFlush(); 
} 
void main() 
{ 
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE); 
    glutInitWindowSize(480, 480); 
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("  "); 
    init(); 
    glutDisplayFunc(Display); 
    glutMainLoop(); 
} 
/* Прототип функции 
void gluNurbsCurve( 
  GLUnurbsObj *nobj, 
  GLint nknots, 
  GLfloat *knot, 
  GLint stride, 
  GLfloat *ctlarray, 
  GLint order, 
  GLenum type 
);*/