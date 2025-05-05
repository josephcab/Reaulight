#ifndef CANAL_H
#define CANAL_H

#include <QObject>
#include <QString>

/**
 * @brief Classe Canal pour gérer les canaux DMX des projecteurs
 */
class Canal : public QObject
{
    Q_OBJECT
    public:
        /**
         * @brief Constructeur de la classe
         * @param parent, objet parent de QT
         */
        Canal(QObject *parent = nullptr);

        /**
         * @brief Méthode renvoyant le type du projecteur
         * @return type du projecteur -> QString
         */
        QString get_type();

        /**
         * @brief Mutateur de la valeur du canal, doit être compris entre 0 et 255 sinon, elle ne sera pas actualisé
         * @param value, compris entre 0 et 255 -> int
         */
        void set_value(int value);

        /**
         * @brief Accesseur de la valeur du canal
         * @return int, valeur du canal
         */
        int get_value();

    private:
        QString type;
        int value;
};

#endif // CANAL_H
