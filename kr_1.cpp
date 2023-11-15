#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include <cmath>
#include <array>

// I want pretty colors for N curves, utility function to convert hue-based HSV to OpenGL compatible RGB
std::array<double, 3> hsv_to_rgb(double H, double S, double V) {
    double s = S / 100;
    double v = V / 100;
    double C = s * v;
    double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    double m = v - C;
    double r, g, b;
    if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    } else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    } else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    } else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    } else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    } else {
        r = C, g = 0, b = X;
    }
    double R = (r + m) * 255;
    double G = (g + m) * 255;
    double B = (b + m) * 255;

    return {R, G, B};
}

const int STEPS = 200;
const int N = 5;
const int K = 6;
double control_points[N + 1][2] = {{-0.9, 0.4},
                                   {-0.7, 0.9},
                                   {-0.5, 0.4},
                                   {-0.3, 0.9},
                                   {-0.1, 0.4},
                                   {0.1,  0.9}};
double knots[N + K + 1] = {0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3};

void drawCurve() {
    glClearColor(0.05, 0.05, 0.05, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5.0);
    glColor3f(1.0, 0, 0);
    glBegin(GL_POINTS);
    for (int i = 0; i < N + 1; ++i) {
        glVertex2d(control_points[i][0], control_points[i][1]);
    }
    glEnd();

    double basis_k[N + 1][STEPS]{};

    glPointSize(1.0);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for (int step = 0; step < STEPS; ++step) {
        double t = (static_cast<double>(step) / STEPS) * (knots[N + 1] - knots[K - 1]) + knots[K - 1];
        double basis[K][N + K]{};
        for (int i = 0; i < N + K; ++i) {
            basis[0][i] = knots[i] <= t && t < knots[i + 1];
        }
        for (int k = 1; k < K; ++k) {
            for (int i = 0; i < N + K - k; ++i) {
                basis[k][i] = 0;
                if (basis[k - 1][i] != 0)
                    basis[k][i] += (t - knots[i]) / (knots[i + k] - knots[i]) * basis[k - 1][i];
                if (basis[k - 1][i + 1] != 0)
                    basis[k][i] += (knots[i + k + 1] - t) / (knots[i + k + 1] - knots[i + 1]) * basis[k - 1][i + 1];
            }
        }
        double x = 0, y = 0;
        for (int i = 0; i <= N; ++i) {
            x += control_points[i][0] * basis[K - 1][i];
            y += control_points[i][1] * basis[K - 1][i];
            basis_k[i][step] = basis[K - 1][i];
        }
        glVertex2d(x, y);
    }
    glEnd();

    for (int i = 0; i <= N; ++i) {
        glColor3dv(hsv_to_rgb(i * 360. / (N + 1), 100, 100).data());
        glBegin(GL_POINTS);
        for (int step = 0; step < STEPS; ++step) {
            glVertex2d(-0.9 + static_cast<double>(step) / STEPS, -0.9 + basis_k[i][step]);
        }
        glEnd();
    }

    glutPostRedisplay();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - B-spline curve");
    glutDisplayFunc(drawCurve);
    glutMainLoop();
    return 0;
}