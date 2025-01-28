#ifndef PROJECTEUR_H
#define PROJECTEUR_H

#include "global.h"
#include <string.h>
#include <QVector3D>

/// @brief Classe permettant de gérer le fonctionnement général d'un projecteur.
class Projecteur
{
    public:
        /// @brief Constructeur de l'objet, initialise sa position et son identifiant
        /// @param pos, poisiton du projecteur dans la scène 3d -> QVector3D
        /// @param address adresse à modifier -> type int
        /// @param distance_attache_rotation distance entre le point d'attache du projecteur et son centre de rotation -> type double
        Projecteur(QVector3D pos, int adress, double distance_attache_rotation);

        /// @brief Accesseur de la position du projecteur dans la scène 3d
        /// @return Position 3d du projecteur sous forme de triplet (x,y,z)
        QVector3D get_pos();

        /// @brief Mutateur de la position courante du projecteur dans la scène
        /// @param pos, position du projecteur dans la scène -> QVector3D
        void set_position(QVector3D pos);

        /// @brief Accesseur de l'addresse du projecteur courant
        /// @return int, adresse du projecteur courant
        int get_address();

        /// @brief Mutateur de l'adresse du projecteur courant
        /// @param id adresse à modifier -> type int
        void set_address(int addresse);

        /// @brief Mutateur du mode courant du projecteur
        /// @param mode mode du projecteur -> type Modes
        void set_mode(Modes mode);

        /// @brief Accesseur du mode courant du projecteur
        /// @return Modes, mode du projecteur
        Modes get_mode();

        /// @brief Mutateur de la couleur du projecteur, si donnée non conforme alors on ne les affectes pas
        /// @param r, couleur rouge du projecteur, ne peut pas être supérieur à 255 ou inférieur à 0 -> int
        /// @param g, couleur verte du projecteur, ne peut pas être supérieur à 255 ou inférieur à 0 -> int
        /// @param b, couleur bleu du projecteur, ne peut pas être supérieur à 255 ou inférieur à 0 -> int
        void set_color(int r, int g, int b);

        /// @brief Accesseur de la couleur du projecteur
        /// @return Color, couleur du projecteur courant
        Color get_color();

        /// @brief Mutateur de l'angle d'éclairage du faisceau lumineux du projecteur en degré, l'angle est reclaculer pour être inférieur à 360 degré
        /// @param angle, angle à attribuer au projecteur -> double
        void set_angle(double angle);

        /// @brief Accesseur de l'angle d'éclairage du faisceau lumineux du projecteur en degré
        /// @return angle, angle d'éclairage du projecteur -> double
        double get_angle();

        /// @brief Mutateur de la taille du projecteur courant
        /// @param height, hauteur du projecteur -> int
        /// @param width, largeur du projecteur -> int
        /// @param dimension, cote du projecteur -> int
        void set_size(int height, int width, int dimension);

        /// @brief Accesseur de la taille du projecteur courant
        /// @return size, taille du projecteut -> size
        Size get_size();

        /// @brief Mutateur de la distance entre le point d'attache du projecteur et son axe de rotation
        /// @param distance, distance à attribuer -> double
        void set_distance_attache_rotation(double distance);

        /// @brief Accesseur de la distance entre le point d'attache du projecteur et son axe de rotation
        /// @param distance, distance courante à récupérer -> double
        double get_distance_attache_rotation();

    private:
        QVector3D pos; // coordonnées du projecteur dans l'espace
        int address; // adresse du projecteur (canaux)
        Modes mode; // mode du projecteur courant
        Color color; // couleur du projecteur sous la forme rgb
        double angle; // angle du faisceau de projecteur en degré
        Size size; // taille du projecteur
        double distance_attache_rotation;
};

#endif // !PROJECTEUR_H
