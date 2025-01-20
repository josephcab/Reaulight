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

    private:
        Position<double> pos; // coordonnées du projecteur dans l'espace
        int address; // adresse du projecteur (canaux)
        Modes mode; // mode du projecteur courant
        Color color; // couleur du projecteur sous la forme rgb
};

#endif // !PROJECTEUR_H
