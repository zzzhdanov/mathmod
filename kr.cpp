#include <iostream>
#include <vector>
#include <GL/glut.h>

GLUnurbsObj* nobj;
// массив точек определяющего многоугольника
//GLfloat ctlarray[][3] = { {-0.9, -0.8, 0.0},{-0.2, 0.8, 0.0},{0.2, -0.5, 0.0},{0.9, 0.8, 0.0} };
//GLfloat ctlarray2[][3] = { {-0.9, -0.8, 0.0},{-0.2, 0.8, 0.0},{-0.2, 0.8, 0.0},
//                            {-0.2, 0.8, 0.0}, {0.2, -0.5, 0.0}, {0.9, 0.8, 0.0} };

GLfloat ctlarray0[][3] = { {-0.9, 0.1, 0.0},
    {-0.7, 0.6, 0.0}, {-0.5, 0.1, 0.0},
    {-0.3, 0.6, 0.0}, {-0.1, 0.1, 0.0},
    {0.1, 0.6, 0.0},  {0.3, 0.1, 0.0},
     {0.5, 0.6, 0.0}, {0.7, 0.1, 0.0},
    {0.9, 0.6, 0.0} };

std::vector <std::vector <double>> B = { {-0.9, 0.1},
    { -0.7, 0.6}, { -0.5, 0.1},
    { -0.3, 0.6}, { -0.1, 0.1},
    { 0.1, 0.6}, { 0.3, 0.1},
    { 0.5, 0.6}, { 0.7, 0.1},
    { 0.9, 0.6} };

double N(int i, int k, double t, const std::vector <double>& x) {
    if (k == 1) {
        if (x[i - 1] <= t && t <= x[i]) {
            return 1.0;
        }
        else return 0.0;
    }
    else {
        double res1 = 0, res2 = 0;
        if ((x[i + k - 2] - x[i - 1]) != 0) {
            res1 = (t - x[i - 1]) * N(i, k - 1, t, x) / (x[i + k - 2] - x[i - 1]);
        }
        if ((x[i + k - 1] - x[i]) != 0) {
            res2 = (x[i + k - 1] - t) * N(i + 1, k - 1, t, x) / (x[i + k - 1] - x[i]);

        }
        return res1 + res2;
    }
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    //создается NURBS-объект
    nobj = gluNewNurbsRenderer();
    // устанавливается свойство неравномерного рационального B-сплайна
      //  GLU_SAMPLING_TOLERANCE – свойство – задает максимальную длину в пикселях
      //  25.0 – значение свойства (используется при разбиении )
    gluNurbsProperty(nobj, GLU_SAMPLING_TOLERANCE, 25.0);
}
void Display() {
    // массив содержащий значения открытого равномерного узлового вектора 
    // всего значений - степень полинома + 1 + кол-во точек, 
    // с равных сторон одинаковое число одинаковых элементов - степень полинома + 1

    //GLfloat knot2[] = { 0.0,0.0,1.0,2.0,3.0,3.0 };
    //GLfloat knot0[] = { 0.0, 0.0, 0.0, 0.0, 0.0,
    //                 1.0, 2.0, 3.0, 4.0, 5.0,
    //                    6.0, 6.0, 6.0, 6.0, 6.0 };
    GLfloat knot[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                       1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

    //std::vector <double> x0 = { 0.0, 0.0, 0.0, 0.0, 0.0,
//                 1.0, 2.0, 3.0, 4.0, 5.0,
//                    6.0, 6.0, 6.0, 6.0, 6.0 };
    std::vector <double> x = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                               1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

    // массив содержащий значения закрытого равномерного узлового вектора 
    //GLfloat knot20[] = { 0.0,1.0,2.0,3.0,4.0,5.0 };

    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(3.0);
    glColor3f(0.0, 0.0, 1.0);

    ////генерация и отображение NURBS кривой 
    //gluNurbsCurve(кривая, knot.size(), knot, ctlarray[0].size(), &ctlarray[0][0], степень полинома + 1, GL_MAP1_VERTEX_3)
    //gluNurbsCurve(nobj, 6, knot2, 3, &ctlarray[0][0], 2, GL_MAP1_VERTEX_3);
    //gluNurbsCurve(nobj, 15, knot0, 3, &ctlarray0[0][0], 5, GL_MAP1_VERTEX_3);
    gluNurbsCurve(nobj, 20, knot, 3, &ctlarray0[0][0], 10, GL_MAP1_VERTEX_3);

    //glColor3f(1.0, 0.3, 1.0);
    //gluNurbsCurve(nobj, 6, knot20, 3, &ctlarray[0][0], 2, GL_MAP1_VERTEX_3);

    glPointSize(4.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < 10; i++) {
        glVertex3f(ctlarray0[i][0], ctlarray0[i][1], ctlarray0[i][2]);
    }
    glEnd();

    //int k = 5;
    int k = 10;
    //double max_in_knot = 6;
    double max_in_knot = 1;
    for (int i = 1; i <= 10; i++) {
        double xB = 0.0, yB = 0.0, xN = 0.0, yN = 0.0;
        glColor3f(0.0, 1.0, 0.0 + (double)i / 10);
        for (double t = 0.00; t <= max_in_knot; t += 0.01) {
            //[0; max_in_knot] - отрезок, на котором построятся базисные функции на оси X
            // масштабируем его на [-1;1]
            //xN = t / 3 - 1;
            xN = t * 2 - 1;
            yN = N(i, k, t, x) - 1;
            if (t != 0.00) {
                glBegin(GL_LINES);
                glVertex3d(xB, yB, 0.0);
                glVertex3d(xN, yN, 0.0);
                glEnd();
            }
            xB = xN;
            yB = yN;
        }
    }

    glFlush();
}
void main() {
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