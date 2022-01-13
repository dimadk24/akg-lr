#ifndef UTILS_H
#define UTILS_H

#define EPSILON 0.000001f

#include <cmath>
#include <algorithm>

#include <QtOpenGL>

//Струкьура точки в 3Д пространстве
struct Point3D {
    Point3D() {
        x = 0, y = 0; z = 0; isVisible = true;
    }
    Point3D(float _x, float _y, float _z) {
        x = _x, y = _y; z = _z; isVisible = true;
    }

    void Set(float _x, float _y, float _z){
        x = _x, y = _y; z = _z; isVisible = true;
    }

    float x, y, z;

    bool isVisible;
};

//Перечисление координатных осей
enum Axis {
    X, Y, Z
};

//Класс вектора в 3Д пространстве
class vec3 {
public:
    float x, y, z;

    //Скалярное произведение векторов
    float dot(const vec3 & b) {
        return vec3::x * b.x + vec3::y * b.y + vec3::z * b.z;
    }

    //Векторное произведение
    vec3 cross(const vec3 & b) {
        return vec3(
            vec3::y * b.z - vec3::z * b.y,
            vec3::z * b.x - vec3::x * b.z,
            vec3::x * b.y - vec3::y * b.x
        );
    }

    //Привести длину вектора к единице
    vec3 normalize() {
        const float s = 1.0f / sqrtf(vec3::x * vec3::x + vec3::y * vec3::y + vec3::z * vec3::z);
        return vec3(vec3::x * s, vec3::y * s, vec3::z * s);
    }

    //Переопределение операторов
    vec3 operator+(const vec3 & b) {
        return vec3(
            vec3::x + b.x,
            vec3::y + b.y,
            vec3::z + b.z
        );
    }
    vec3 operator+=(const vec3 & b) {
        *this = vec3::operator+(b);
        return *this;
    }

    vec3 operator-(const vec3 & b) {
        return vec3(
            vec3::x - b.x,
            vec3::y - b.y,
            vec3::z - b.z
        );
    }
    vec3 operator-=(const vec3 & b) {
        *this = vec3::operator-(b);
        return *this;
    }

    vec3 operator*(const vec3 & b) {
        return vec3(
            vec3::x * b.x,
            vec3::y * b.y,
            vec3::z * b.z
        );
    }
    vec3 operator*=(const vec3 & b) {
        *this = vec3::operator*(b);
        return *this;
    }
    vec3 operator*(float b) {
        return vec3(
            vec3::x * b,
            vec3::y * b,
            vec3::z * b
        );
    }
    vec3 operator*=(float b) {
        *this = vec3::operator*(b);
        return *this;
    }

    vec3 operator/(const vec3 & b) {
        return vec3(
            vec3::x / b.x,
            vec3::y / b.y,
            vec3::z / b.z
        );
    }
    vec3 operator/=(const vec3 & b) {
        *this = vec3::operator/(b);
        return *this;
    }
    vec3 operator/(float b) {
        return vec3(
            vec3::x * b,
            vec3::y * b,
            vec3::z * b
        );
    }
    vec3 operator/=(float b) {
        *this = vec3::operator/(b);
        return *this;
    }

    //Конструкторы
    vec3(float x, float y, float z) {
        vec3::x = x;
        vec3::y = y;
        vec3::z = z;
    }
    vec3(float x) {
        vec3::x = x;
        vec3::y = x;
        vec3::z = x;
    }
    vec3() {
        //
    }

    //Деструктор
    ~vec3() {
        //
    }
};

//Функция создания матрицы поворота
void CreateRotateMatrix(float* mtx, float angle, Axis axis);

//Проверка пересечения отрезка с прямоугольником
bool CheckRayIntersectRectangle(Point3D* eye_point, Point3D* target_point,
                                Point3D* rect_p1, Point3D* rect_p2, Point3D* rect_p3, Point3D* rect_p4);

//Приведение сферических координат в декартовы
void SphereToPoint3D(double r, double phi, double theta, Point3D* point);

//Проверка пересечения отрезка с треугольником
bool lineSegIntersectTri(
    vec3 line[2],
    vec3 tri[3],
    vec3 * point
);
#endif // UTILS_H
