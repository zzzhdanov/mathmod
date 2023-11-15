#include <GL/glut.h>
#include <math.h>

// Количество управляющих точек
#define NUM_CONTROL_POINTS 9

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0, 5.0, -2.0, 2.0);
}

void drawCurve() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0);
    glColor3f(0.0, 0.0, 0.0);

    // Управляющие точки для создания синусоидального B-сплайна
    GLfloat ctrlPoints[NUM_CONTROL_POINTS][3] = {
        { -4, -1, 0 },
        { -3,1, 0 },
        { -2, 1, 0 },
        { -1, -1, 0 },
        { 0, 1, 0 },
        { 1, -1, 0 },
        { 2, 1, 0 },
        { 3, -1, 0 },
        { 4, 1, 0 }
    };

    // Рисование управляющих точек
    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_CONTROL_POINTS; i++) {
        glVertex3fv(&ctrlPoints[i][0]);
    }
    glEnd();

    // Рисование B-сплайна
    glColor3f(0.0, 1.0, 0.0);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, NUM_CONTROL_POINTS, &ctrlPoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; i++) {
        glEvalCoord1f((GLfloat)i / 100.0);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sinusoidal B-Spline Curve");
    init();
    glutDisplayFunc(drawCurve);
    glutMainLoop();
    return 0;
}
