#include "triangle.h"

/**
 * @brief Triangle::Triangle Permet d'instancier un triangle
 * @details Instancie un triangle nul (les trois points à l'origine)
 */
Triangle::Triangle()
    : triangle {QVector3D(0,0,0),QVector3D(0,0,0),QVector3D(0,0,0)}
{}

/**
 * @brief Triangle::Triangle Permet d'instancier un triangle
 * @details Instancie un triangle basé sur les trois points fournis en paramètre.
 * @param a le premier point du triangle
 * @param b le second point du triangle
 * @param c le dernier point du triangle
 */
Triangle::Triangle(QVector3D a, QVector3D b, QVector3D c)
    : triangle {a,b,c}
{}

/**
 * @brief Triangle::setPoint permet de mettre à jour les coordonnées d'un point du triangle
 * @param id l'identifiant du point à modifier (entre 0 et 2)
 * @param point les nouvelles coordonnées du point
 */
void Triangle::setPoint(int id, QVector3D point)
{
    if(id >=0 && id < 3)
        triangle[id] = point;
}

/**
 * @brief Triangle::setTriangle permet de redéfinir intégralement le triangle à partir d'un tableau de 3 points
 * @param points Le tableau des trois points à remplacer (points en 3D)
 */
void Triangle::setTriangle(QVector3D points[3])
{
    for(int i = 0; i < 3; i++)
    {
        triangle[i] = points[i];
    }

}

/**
 * @brief Triangle::getPoint Permet de récupérer les coordonnées de l'un des points du triangle
 * @param id l'identifiant (entre 0 et 2) du point à récupérer
 * @return le point demandé
 */
QVector3D Triangle::getPoint(int id) const
{
    if(id >= 0 && id < 3)
        return triangle[id];
    else
        return QVector3D(0,0,0);
}
