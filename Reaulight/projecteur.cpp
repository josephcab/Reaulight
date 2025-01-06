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
