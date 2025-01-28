#ifndef GLOBAL_H
#define GLOBAL_H

// type enuméré contenant les modes des différents projecteurs
enum Modes
{

};

// structure gérant les couleurs sous le format rgb de 0 à 255
struct Color
{
    int r;
    int g;
    int b;
};

// Taille du projecteur en mm
struct Size
{
    int height; // hauteur
    int width; // largeur
    int dimension; // cote
};

#endif // GLOBAL_H
