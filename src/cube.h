#ifndef CUBE_H
#define CUBE_H

#include <QtOpenGL>
#include <vector>
#include "utils.h"

//КЛасс куба
class Cube
{
public:
    //Конструктор
    Cube();
    //Деструктор
    ~Cube();

    //Длина стороны
    double A = 4;

    //Мотод отрисовки
    void Draw();
    //Метод вращения
    void Rotate(float angle, Axis axis);
    //Метод проверки видимости вершин
    void CheckVisibility(Point3D* eye_point);

private:
    //Массив вершин
    Point3D* vertexes;
};

#endif // CUBE_H
