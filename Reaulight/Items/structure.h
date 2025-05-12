#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <QObject>
#include <QList>
#include <QDebug>
#include <QString>
#include <QJsonDocument>
#include <QVector3D>
#include <QPair>


class Structure : public QObject
{
    Q_OBJECT

    public:
        explicit Structure(QObject *parent=nullptr);
        Structure(QString fileName, QObject *parent = nullptr);
        Structure(QJsonDocument document, QObject *parent = nullptr);


        /**
         * @brief Renvoie le nom de la structure courante
         * @return QString Nom de la structure
         */
        QString getName();
        unsigned int getDiameter();


        /**
         * @brief Mutateur du nom de la structure
         * @param name:QString nom de la structure
         */
        void setName(QString name);
        void setFilename(QString filename);
        void setDiameter(unsigned int diameter);


        void setAxes(QList<QPair<QVector3D, QVector3D> > axes);
        void setAxe(unsigned int id, QVector3D start, QVector3D end);
        void setAxe(unsigned int id, QPair<QVector3D, QVector3D> axe);

        QList<QPair<QVector3D, QVector3D> > getAxes();
        QPair<QVector3D, QVector3D> getAxe(unsigned int id);

        QJsonDocument getJSON() const;
        QString getFilename() const;

    public slots:
        void load();
        void load(QString filename);
        void load(QJsonDocument document);
        void save();
        void save(QString filename);

    private:
        QString name; // Nom de la structure
        QString filename; // Référence du fichier
        QList<QPair<QVector3D, QVector3D> > axes; //Les différents axes de la structure
        unsigned int diameter; // Diamètre des tubes
};

#endif // STRUCTURE_H
