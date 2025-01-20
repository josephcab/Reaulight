#include "salledespectacle.h"

SalleDeSpectacle::SalleDeSpectacle(QObject *parent)
    : QObject{parent}
{

}

SalleDeSpectacle::SalleDeSpectacle(QString fileName, QObject *parent)
    : QObject{parent}
{

}

QList<QVector3D> SalleDeSpectacle::get_ground()
{

}

QList<QVector3D> SalleDeSpectacle::get_roof()
{

}

QList<QVector3D> SalleDeSpectacle::get_layer(int layer)
{

}

void SalleDeSpectacle::set_ground(QList<QVector3D> ground_points)
{

}

void SalleDeSpectacle::set_roof(QList<QVector3D> roof_points)
{

}

void SalleDeSpectacle::set_layer(QList<QVector3D> layer_points, int layer)
{

}
