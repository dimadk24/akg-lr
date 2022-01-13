#include "cube.h"

Cube::Cube() {
    vertexes = new Point3D[4];
    (vertexes + 0)->Set(-3, 5, -3);
    (vertexes + 1)->Set(-3,  -5, -3);
    (vertexes + 2)->Set(6,  0, -3);
    (vertexes + 3)->Set( 0, 0, 6);
}

Cube::~Cube(){
    delete[] vertexes;
}

void Cube::Draw(){
    glLineWidth(2);
    glColor3d(0.5, 0.5, 0.5);

    if(!(vertexes + 0)->isVisible || !(vertexes + 1)->isVisible){
        glEnable(GL_LINE_STIPPLE);
        glLineStipple( 1, 0xFFF8);
    }
    glBegin(GL_LINES);
        glVertex3d((vertexes + 0)->x, (vertexes + 0)->y, (vertexes + 0)->z);
        glVertex3d((vertexes + 1)->x, (vertexes + 1)->y, (vertexes + 1)->z);
    glEnd();
    if(!(vertexes + 0)->isVisible || !(vertexes + 1)->isVisible){
        glDisable(GL_LINE_STIPPLE);
    }

    if(!(vertexes + 1)->isVisible || !(vertexes + 2)->isVisible){
        glEnable(GL_LINE_STIPPLE);
        glLineStipple( 1, 0xFFF8);
    }
    glBegin(GL_LINES);
        glVertex3d((vertexes + 1)->x, (vertexes + 1)->y, (vertexes + 1)->z);
        glVertex3d((vertexes + 2)->x, (vertexes + 2)->y, (vertexes + 2)->z);
    glEnd();
    if(!(vertexes + 1)->isVisible || !(vertexes + 2)->isVisible){
        glDisable(GL_LINE_STIPPLE);
    }

    if(!(vertexes + 2)->isVisible || !(vertexes + 3)->isVisible){
        glEnable(GL_LINE_STIPPLE);
        glLineStipple( 1, 0xFFF8);
    }
    glBegin(GL_LINES);
        glVertex3d((vertexes + 2)->x, (vertexes + 2)->y, (vertexes + 2)->z);
        glVertex3d((vertexes + 3)->x, (vertexes + 3)->y, (vertexes + 3)->z);
    glEnd();
    if(!(vertexes + 2)->isVisible || !(vertexes + 3)->isVisible){
        glDisable(GL_LINE_STIPPLE);
    }

    if(!(vertexes + 3)->isVisible || !(vertexes + 0)->isVisible){
        glEnable(GL_LINE_STIPPLE);
        glLineStipple( 1, 0xFFF8);
    }
    glBegin(GL_LINES);
        glVertex3d((vertexes + 3)->x, (vertexes + 3)->y, (vertexes + 3)->z);
        glVertex3d((vertexes + 0)->x, (vertexes + 0)->y, (vertexes + 0)->z);
    glEnd();
    if(!(vertexes + 3)->isVisible || !(vertexes + 0)->isVisible){
        glDisable(GL_LINE_STIPPLE);
    }

    if(!(vertexes + 2)->isVisible || !(vertexes + 0)->isVisible){
        glEnable(GL_LINE_STIPPLE);
        glLineStipple( 1, 0xFFF8);
    }
    glBegin(GL_LINES);
        glVertex3d((vertexes + 2)->x, (vertexes + 2)->y, (vertexes + 2)->z);
        glVertex3d((vertexes + 0)->x, (vertexes + 0)->y, (vertexes + 0)->z);
    glEnd();
    if(!(vertexes + 2)->isVisible || !(vertexes + 0)->isVisible){
        glDisable(GL_LINE_STIPPLE);
    }

    if(!(vertexes + 3)->isVisible || !(vertexes + 1)->isVisible){
        glEnable(GL_LINE_STIPPLE);
        glLineStipple( 1, 0xFFF8);
    }
    glBegin(GL_LINES);
        glVertex3d((vertexes + 3)->x, (vertexes + 3)->y, (vertexes + 3)->z);
        glVertex3d((vertexes + 1)->x, (vertexes + 1)->y, (vertexes + 1)->z);
    glEnd();
    if(!(vertexes + 1)->isVisible || !(vertexes + 1)->isVisible){
        glDisable(GL_LINE_STIPPLE);
    }





    glPointSize(10);
    for(Point3D* ptr = vertexes; ptr < vertexes + 8; ptr++){
        if(ptr->isVisible)
            glColor3d(0.1, 0.1, 1.0);
        else
            glColor3d(1.0, 0.1, 0.0);
        glBegin(GL_POINTS);
        glVertex3d(ptr->x, ptr->y, ptr->z);
        glEnd();
    }
}

void Cube::Rotate(float angle, Axis axis){
    float newX, newY, newZ;
    float matrix[4][4];
    CreateRotateMatrix(&matrix[0][0], angle, axis);

    for(Point3D* ptr = vertexes; ptr < vertexes + 8; ptr++){
        newX = matrix[0][0] * ptr->x + matrix[1][0] * ptr->y + matrix[2][0] * ptr->z + matrix[3][0];
        newY = matrix[0][1] * ptr->x + matrix[1][1] * ptr->y + matrix[2][1] * ptr->z + matrix[3][1];
        newZ = matrix[0][2] * ptr->x + matrix[1][2] * ptr->y + matrix[2][2] * ptr->z + matrix[3][2];
        ptr->x = newX; ptr->y = newY; ptr->z = newZ;
    }
}

void Cube::CheckVisibility(Point3D* eye_point){
    (vertexes + 0)->isVisible = !(CheckRayIntersectRectangle(eye_point, vertexes + 0, vertexes + 1, vertexes + 2, vertexes + 6, vertexes + 5) ||
                                CheckRayIntersectRectangle(eye_point, vertexes + 0, vertexes + 2, vertexes + 6, vertexes + 7, vertexes + 3) ||
                                CheckRayIntersectRectangle(eye_point, vertexes + 0, vertexes + 4, vertexes + 5, vertexes + 6, vertexes + 7));

    (vertexes + 1)->isVisible = !(CheckRayIntersectRectangle(eye_point, vertexes + 1, vertexes + 2, vertexes + 6, vertexes + 7, vertexes + 3) ||
                                CheckRayIntersectRectangle(eye_point, vertexes + 1, vertexes + 0, vertexes + 3, vertexes + 7, vertexes + 4) ||
                                CheckRayIntersectRectangle(eye_point, vertexes + 1, vertexes + 4, vertexes + 5, vertexes + 6, vertexes + 7));

    (vertexes + 2)->isVisible = !(CheckRayIntersectRectangle(eye_point, vertexes + 2, vertexes + 0, vertexes + 1, vertexes + 5, vertexes + 4) ||
                                CheckRayIntersectRectangle(eye_point, vertexes + 2, vertexes + 0, vertexes + 3, vertexes + 7, vertexes + 4) ||
                                CheckRayIntersectRectangle(eye_point, vertexes + 2, vertexes + 4, vertexes + 5, vertexes + 6, vertexes + 7));

    (vertexes + 3)->isVisible = !(CheckRayIntersectRectangle(eye_point, vertexes + 3, vertexes + 0, vertexes + 1, vertexes + 5, vertexes + 4) ||
                                CheckRayIntersectRectangle(eye_point, vertexes + 3, vertexes + 1, vertexes + 2, vertexes + 6, vertexes + 7) ||
                                CheckRayIntersectRectangle(eye_point, vertexes + 3, vertexes + 4, vertexes + 5, vertexes + 6, vertexes + 7));
}
