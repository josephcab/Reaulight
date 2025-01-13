#include "projecteur.h"

Projecteur::Projecteur(double x, double y, double z, int address)
{
    // Attribution de la position
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;

    // Attribution de l'identifiant
    this->address = address;
}

Position<double> Projecteur::get_pos()
{
    return this->pos;
}

void Projecteur::set_position(double x, double y, double z)
{
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;
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
