#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <qobject.h>
#include <QList>
#include <QDebug>
#include <QString>

#include "projector.h"

class Structure : public QObject
{
    Q_OBJECT

    public:
        Structure(QObject *parent=nullptr);

        /**
         * @brief Accesseur de l'identifiant de la structure courante
         * @return int identifiant de la structure courante
         */
        int get_id();

        /**
         * @brief Renvoie le propriétaire de la structure courante
         * @return QString Nom du propriétaire
         */
        QString get_owner();

        /**
         * @brief Renvoie le nom de la structure courante
         * @return QString Nom de la structure
         */
        QString get_name();

        /**
         * @brief Mutateur de l'indentifiant de la structure
         * @param id:int identifiant de la structure
         */
        void set_id(int id);

        /**
         * @brief Mutateur du propriétaire de la structure
         * @param owner:QString propriétaire de la structure
         */
        void set_owner(QString owner);

        /**
         * @brief Mutateur du nom de la structure
         * @param name:QString nom de la structure
         */
        void set_name(QString name);

        /// @brief Accesseur de la liste des instances de projecteur
        /// @param index, index de la liste auquel accéder -> type int
        /// @return projecteur associé à l'index en paramètre, renvoie un pointeur nulle si index out of range -> type Projecteur
        Projector* get_projector(int index);

        /// @brief Méthode permettant d'instancier un projecteur dans la scène
        /// @param pos, poisiton du projecteur dans la scène 3d -> QVector3D
        /// @param address adresse à modifier -> type int
        /// @param distance_attache_rotation distance entre le point d'attache du projecteur et son centre de rotation -> type double
        /// @param angle, angle d'éclairage du projecteur courant -> type double
        void add_projector(QVector3D pos, int adress, double distance_attache_rotation, double angle);

        /// @brief Méthode permettant de désinstancier un projecteur en y accédant via son index
        /// @param index, index du projecteur à désintancier -> type int
        void remove_projector(int index);

    private:
        int id;
        QString owner; // Propriétaire
        QString name; // Nom de la structure
        QVector3D position;
        QList<Projector *> projectors;
};

#endif // STRUCTURE_H
