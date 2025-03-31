#include "structure.h"

Structure::Structure(QObject *parent) : QObject{parent}
{

}

int Structure::get_id()
{
    return this->id;
}

QString Structure::get_owner()
{
    return this->owner;
}

QString Structure::get_name()
{
    return this->name;
}

void Structure::set_id(int id)
{
    this->id = id;
}

void Structure::set_owner(QString owner)
{
    this->owner = owner;
}

void Structure::set_name(QString name)
{
    this->name = name;
}

Projector* Structure::get_instanced_projector(int index)
{
    if ((int)(this->instanced_projector.size()) > index && index >= 0)
        return this->instanced_projector[index];
    else
        return nullptr;
}

void Structure::instance_projector(QVector3D pos, int adress, double distance_attache_rotation, double angle)
{
    this->instanced_projector.append(new Projector(pos, adress, distance_attache_rotation, angle, nullptr));
}

void Structure::uninstance_projector(int index)
{
    // on regarde si on a un index out of range
    if ((int)(this->instanced_projector.size()) > index && index >= 0)
    {
        delete this->instanced_projector[index]; // désintancie le projecteur
        this->instanced_projector.erase(this->instanced_projector.begin() + index); // supprime un élément à un index
    }
    else // si oui, on lève une erreur
    {
        qDebug() << "List index out of range, vous ne pouvez pas supprimer un projecteur à un emplacement mémoire indéfinie";
    }
}

