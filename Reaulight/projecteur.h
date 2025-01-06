#ifndef PROJECTEUR_H
#define PROJECTEUR_H

#include "global.h"
#include <string.h>

/// @brief Classe permettant de gérer le fonctionnement général d'un projecteur.
class Projecteur
{
    public:
        /// @brief Constructeur de l'objet, initialise sa position et son identifiant
        /// @param x position x du projecteur -> type double
        /// @param y position y du projecteur -> type double
        /// @param z position z du projecteur -> type double
        /// @param address adresse à modifier -> type int
        Projecteur(double x, double y, double z, int adress);

        /// @brief Accesseur de la position du projecteur dans la scène 3d
        /// @return Position 3d du projecteur sous forme de triplet (x,y,z)
        Position<double> get_pos();

        /// @brief Mutateur de la position courante du projecteur dans la scène
        /// @param x position x du projecteur -> type double
        /// @param y position y du projecteur -> type double
        /// @param z position z du projecteur -> type double
        void set_position(double x, double y, double z);

        /// @brief Accesseur de l'addresse du projecteur courant
        /// @return int, adresse du projecteur courant
        int get_address();

        /// @brief Mutateur de l'adresse du projecteur courant
        /// @param id adresse à modifier -> type int
        void set_address(int addresse);

    private:
        Position<double> pos; // coordonnées du projecteur dans l'espace
        int address; // adresse du projecteur
        Modes mode; // mode du projecteur courant
        Color color; // couleur du projecteur sous la forme rgb
};

#endif // !PROJECTEUR_H
