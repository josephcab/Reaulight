#ifndef GLOBAL_H
#define GLOBAL_H

// Structure permettant de gérer le positionnement dans l'espace d'un élément donné
// peut être utilisé avec n'importe quel type de donné du moment que son utilisation est cohérente
template <typename type> struct Position
{
    type x;
    type y;
    type z;
};

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

#endif // GLOBAL_H
