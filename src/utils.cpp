#include "utils.h"

void CreateRotateMatrix(float* mtx, float angle, Axis axis) {
    float* ptr = mtx;
    switch (axis) {
    case X:
        *(ptr++) = 1; *(ptr++) = 0;             *(ptr++) = 0;           *(ptr++) = 0;
        *(ptr++) = 0; *(ptr++) = cos(angle);    *(ptr++) = sin(angle);  *(ptr++) = 0;
        *(ptr++) = 0; *(ptr++) = -sin(angle);   *(ptr++) = cos(angle);  *(ptr++) = 0;
        *(ptr++) = 0; *(ptr++) = 0;             *(ptr++) = 0;           *(ptr++) = 1;
        break;
    case Y:
        *(ptr++) = cos(angle);  *(ptr++) = 0;   *(ptr++) = -sin(angle); *(ptr++) = 0;
        *(ptr++) = 0;           *(ptr++) = 1;   *(ptr++) = 0;           *(ptr++) = 0;
        *(ptr++) = sin(angle);  *(ptr++) = 0;   *(ptr++) = cos(angle);  *(ptr++) = 0;
        *(ptr++) = 0;           *(ptr++) = 0;   *(ptr++) = 0;           *(ptr++) = 1;
        break;
    case Z:
        *(ptr++) = cos(angle);  *(ptr++) = sin(angle);  *(ptr++) = 0;   *(ptr++) = 0;
        *(ptr++) = -sin(angle); *(ptr++) = cos(angle);  *(ptr++) = 0;   *(ptr++) = 0;
        *(ptr++) = 0;           *(ptr++) = 0;           *(ptr++) = 1;   *(ptr++) = 0;
        *(ptr++) = 0;           *(ptr++) = 0;           *(ptr++) = 0;   *(ptr++) = 1;
        break;
    }
}

bool CheckRayIntersectRectangle(Point3D* eye_point, Point3D* target_point,
                                Point3D* rect_p1, Point3D* rect_p2, Point3D* rect_p3, Point3D* rect_p4){
    vec3 tri1[3] = {
            { rect_p1->x, rect_p1->y,rect_p1->z },
            { rect_p2->x, rect_p2->y,rect_p2->z },
            { rect_p3->x, rect_p3->y,rect_p3->z },
        };

    vec3 tri2[3] = {
            { rect_p1->x, rect_p1->y,rect_p1->z },
            { rect_p3->x, rect_p3->y,rect_p3->z },
            { rect_p4->x, rect_p4->y,rect_p4->z },
        };

    vec3 line[2] = {
            { eye_point->x, eye_point->y, eye_point->z },
            { target_point->x, target_point->y, target_point->z },
        };


    int check1 = lineSegIntersectTri(line, tri1, NULL);
    int check2 = lineSegIntersectTri(line, tri2, NULL);

    return check1 || check2;
}

void SphereToPoint3D(double r, double phi, double theta, Point3D* point){
    point->x = r * sin(theta) * cos(phi);
    point->y = r * sin(theta) * sin(phi);
    point->z = r * cos(theta);
}

bool lineSegIntersectTri( vec3 line[2], vec3 tri[3],  vec3 * point){
    vec3 e0 = tri[1] - tri[0];
    vec3 e1 = tri[2] - tri[0];

    vec3 dir = line[1] - line[0];
    vec3 dir_norm = dir.normalize();

    vec3 h = dir_norm.cross(e1);
    const float a = e0.dot(h);

    if (a > -EPSILON && a < EPSILON) {
        return false;
    }

    vec3 s = line[0] - tri[0];
    const float f = 1.0f / a;
    const float u = f * s.dot(h);

    if (u < 0.0f || u > 1.0f) {
        return false;
    }

    vec3 q = s.cross(e0);
    const float v = f * dir_norm.dot(q);

    if (v < 0.0f || u + v > 1.0f) {
        return false;
    }

    const float t = f * e1.dot(q);

    if (t > EPSILON && t < sqrtf(dir.dot(dir))) {
        if (point) {
            *point = line[0] + dir_norm * t;
        }

        return true;
    }

    return false;
}
