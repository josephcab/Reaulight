#ifndef SCENE_H
#define SCENE_H

#include "Items/triangle.h"
#include <QObject>
#include <QList>
#include <QVector3D>
#include <QJsonDocument>
#include <QFile>

class Scene : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief La classe Scène
     * @details La classe Scene est un classe permettant de représenter une une scène.
     *          Chaque scène s'insère dans une salle de spectacle. chaque salle de spectacle
     *          peut disposer de plusieurs scènes. Pour ce faire, elle définit au moins deux couches de points (Dessus de scène et plafond).
     *          Elle peut prendre en paramètre de création un fichier de définition de salle, ou un QJsonDocument
     *          représentant la salle.
     */
    explicit Scene(QObject *parent = nullptr);
    Scene(QString fileName, QObject *parent = nullptr);
    Scene(QJsonDocument document, QObject *parent = nullptr);

    Triangle get_triangle(int trig);
    QList<Triangle> get_triangles();

    void set_triangle(Triangle trig, int pos);

    QJsonDocument get_JSON();

public slots:
    void load();
    void load(QString filename);
    void load(QJsonDocument document);
    void save();
    void save(QString filename);

private:
    QList<Triangle> *border;
    QString filename;
    QString sceneName;

signals:

};

#endif // SCENE_H
