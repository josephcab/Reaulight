#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QString>

// TO DO : Mettre une plage de valeur pour les valeurs du canal courant et faire en sorte de ne pas envoyer une valeur qui n'est pas dans cette plage

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
         * @param range_value:QList<int>, plage de valeurs pouvant être prise en charge par le canal, la première valeur doit être inférieur ou égale à la seconde sinon la plage sera entre 0 et 255
         * @param parent:QObject, objet parent de QT
         */
        Channel(int place, QList<int> range_value, QObject *parent = nullptr);

        /**
         * @brief Méthode renvoyant le type du projecteur
         * @return type du projecteur -> QString
         */
        QString get_type();

        /**
         * @brief Mutateur de la plage de valeurs du canal, première valeur <= seconde valeur
         * @param range:QList<int>, plage de valeur du canal
         */
        void set_range_value(QList<int> range);

        /**
         * @brief Accesseur de la plage de valeurs du canal courant
         * @return plage de valeurs du canal courant -> QList<int>
         */
        QList<int> get_range_value();

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
         * @param value:int, compris entre les bornes prédéfinient pour le canal courant
         */
        void set_value(int value);

        /**
         * @brief Accesseur de la valeur associé au canal rouge
         * @return int, valeur associé au canal
         */
        int get_value();

    protected:
        QString type;
        int place;
        int value;
        QList<int> range_value;
};

/**
 * @brief Classe canal pour gérer l'eclairage de projecteur courant
 */
class ChannelDimmer : public Channel
{
    Q_OBJECT
    public:
        ChannelDimmer(int place, QList<int> range_value, QObject *parent = nullptr);
};

/**
 * @brief Classe canal pour gérer le fonctionnement du stroboscope du projecteur courant
 */
class ChannelStrobe : public Channel
{
    Q_OBJECT
    public:
        ChannelStrobe(int place, QList<int> range_value, QObject *parent = nullptr);
};

/**
 * @brief Classe gérant le mode son de certains projecteurs
 */
class ChannelSound : public Channel
{
    Q_OBJECT
    public:
        ChannelSound(int place, QList<int> range_value, QObject *parent = nullptr);
};

/**
 * @brief Classe canal pour gérer un canal de couleur rouge
 */
class ChannelR : public Channel
{
    Q_OBJECT
    public:
        ChannelR(int place, QList<int> range_value, QObject *parent = nullptr);
};

/**
 * @brief Classe canal pour gérer un canal de couleur verte
 */
class ChannelG : public Channel
{
    Q_OBJECT
    public:
        ChannelG(int place, QList<int> range_value, QObject *parent = nullptr);
};

/**
 * @brief Classe canal pour gérer un canal de couleur bleu
 */
class ChannelB : public Channel
{
    Q_OBJECT
    public:
        ChannelB(int place, QList<int> range_value, QObject *parent = nullptr);
};

#endif // CHANNEL_H
