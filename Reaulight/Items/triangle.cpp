#include "triangle.h"

Triangle::Triangle()
    : /*QObject{parent},*/ triangle {QVector3D(0,0,0),QVector3D(0,0,0),QVector3D(0,0,0)}
{}


Triangle::Triangle(QVector3D a, QVector3D b, QVector3D c)
    : /*QObject{parent},*/ triangle {a,b,c}
{}

void Triangle::setPoint(int id, QVector3D point)
{
    triangle[id] = point;
}

void Triangle::setTriangle(QVector3D points[3])
{
    for(int i = 0; i < 3; i++)
    {
        triangle[i] = points[i];
    }

}

QVector3D Triangle::getPoint(int id) const
{
    return triangle[id];
}
