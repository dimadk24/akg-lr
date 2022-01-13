#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    :QOpenGLWidget(parent) {
    eye_point = new Point3D();
    SphereToPoint3D(12, 2, 2, eye_point);
}

OpenGLWidget::~OpenGLWidget() {
    delete eye_point;
}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(255.0, 255.0, 255.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DOUBLEBUFFER);
    glDepthFunc(GL_LESS);
}

void OpenGLWidget::resizeGL(int w, int h) {
    const float ar = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar * 0.7, ar * 0.7, -1.0, 1.0, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawAxes(void) {
    glLineWidth(1);

    glBegin(GL_LINES);
    glColor3f(2, 0, 0); glVertex3f(-10, 0, 0); glVertex3f(50, 0, 0);
    glColor3f(0, 2, 0); glVertex3f(0, -10, 0); glVertex3f(0, 50, 0);
    glColor3f(0, 0, 2); glVertex3f(0, 0, -10); glVertex3f(0, 0, 50);
    glEnd();
}


void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(eye_point->x, eye_point->y, eye_point->z, 0, 0, 0, 0, 1, 0);

    drawAxes();
    cube.CheckVisibility(eye_point);
    cube.Draw();

    glFlush();
    this->makeCurrent();

}
