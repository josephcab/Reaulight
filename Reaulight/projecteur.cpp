#include "projecteur.h"

Projecteur::Projecteur(QVector3D pos, int address, double distance_attache_rotation)
{
    // Attribution de la position
    this->pos = pos;

    // Attribution de l'identifiant
    this->address = address;

    this->distance_attache_rotation = distance_attache_rotation;
}

QVector3D Projecteur::get_pos()
{
    return this->pos;
}

void Projecteur::set_position(QVector3D pos)
{
    this->pos = pos;
}

int Projecteur::get_address()
{
    return this->address;
}

void Projecteur::set_address(int address)
{
    this->address = address;
}

void Projecteur::set_mode(Modes mode)
{
    this->mode = mode;
}

Modes Projecteur::get_mode()
{
    return this->mode;
}

void Projecteur::set_color(int r, int g, int b)
{
    if (r >= 0 && r <= 255)
        this->color.r = r;

    if (g >= 0 && g <= 255)
        this->color.g = g;

    if (b >= 0 && b <= 255)
        this->color.b = b;
}

Color Projecteur::get_color()
{
    return this->color;
}

void Projecteur::set_angle(double angle)
{
    if (angle >= 0 && angle < 360)
        this->angle = angle;
    else if (angle == 360)
        this->angle = 0;
    else if (angle > 360)
    {
        while (angle > 360)
            angle -= 360;
        this->angle = angle;
    }
}

double Projecteur::get_angle()
{
    return this->angle;
}

void Projecteur::set_size(int height, int width, int dimension)
{
    // si les tailles sont négatives ou nulles, on n'attribut pas
    if (height > 0)
        this->size.height = height;
    if (width > 0)
        this->size.width = width;
    if (dimension > 0)
        this->size.dimension = dimension;
}

Size Projecteur::get_size()
{
    return this->size;
}

void Projecteur::set_distance_attache_rotation(double distance)
{
    this->distance_attache_rotation = distance;
}

double Projecteur::get_distance_attache_rotation()
{
    return this->distance_attache_rotation;
}
