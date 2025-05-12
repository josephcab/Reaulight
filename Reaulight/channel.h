#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QString>

/**
 * @brief Classe Canal pour gérer les canaux DMX des projecteurs
 */
class Channel : public QObject
{
    Q_OBJECT
    public:
        /**
         * @brief Constructeur de la classe
         * @param place:int, place du projecteur dans l'univer DMX
         * @param parent:QObject, objet parent de QT
         */
        Channel(int place, QObject *parent = nullptr);

        /**
         * @brief Méthode renvoyant le type du projecteur
         * @return type du projecteur -> QString
         */
        QString get_type();

        /**
         * @brief Mutateur de la place du canal dans l'univer, doit être compris entre 0 et 255 sinon, elle ne sera pas actualisé
         * @param place:int, compris entre 0 et 255
         */
        void set_place(int place);

        /**
         * @brief Accesseur de la place du canal dans l'univer DMX
         * @return int, place du canal
         */
        int get_place();

    private:
        QString type;
        int place;
};

#endif // CHANNEL_H
