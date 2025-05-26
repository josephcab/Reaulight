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

        /**
         * @brief Mutateur de la valeur associé au canal du projecteur.
         * @param value:int, compris entre 0 et 255
         */
        void set_value(int value);

        /**
         * @brief Accesseur de la valeur associé au canal rouge
         * @return int, valeur associé au canal
         */
        int get_value();

    private:
        QString type;
        int place;
        int value;
};

/**
 * @brief Classe canal pour gérer un canal de couleur rouge
 */
class ChannelR : public QObject, public Channel
{
    Q_OBJECT
    public:
        ChannelR(int place, QObject *parent = nullptr);
};

/**
 * @brief Classe canal pour gérer un canal de couleur verte
 */
class ChannelG : public QObject, public Channel
{
    Q_OBJECT
    public:
        ChannelG(int place, QObject *parent = nullptr);
};

/**
 * @brief Classe canal pour gérer un canal de couleur bleu
 */
class ChannelB : public QObject, public Channel
{
    Q_OBJECT
    public:
        ChannelB(int place, QObject *parent = nullptr);
};

#endif // CHANNEL_H
