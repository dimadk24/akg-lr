#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <GL/glu.h>

#include "cube.h"

//Класс виджета OpenGL
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    //Конструктор
    OpenGLWidget(QWidget *parent = 0);
    //Деструктор
    ~OpenGLWidget();

    //Углы поворота куба
    double rotate_x=0;
    double rotate_y=0;
    double rotate_z=0;

    //Куб
    Cube cube;

    //Точка обзора
    Point3D* eye_point;

protected:
    //Инициализация OpenGL
    void initializeGL();
    //Метод отрисовки сцены
    void paintGL();
    //Метод изменения размеров виджета
    void resizeGL(int w, int h);
};

#endif // OPENGLWIDGET_H
