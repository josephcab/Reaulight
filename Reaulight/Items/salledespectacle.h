#ifndef SALLEDESPECTACLE_H
#define SALLEDESPECTACLE_H

#include <QObject>
#include <QList>
#include <QVector3D>
#include <QJsonDocument>
#include <QFile>

#include "triangle.h"

/**
 * @brief The SalleDeSpectacle class
 * @details La classe SalleDeSpectacle est un classe permettant de représenter une salle de spectacle.
 *          Pour ce faire, elle définit un ensemble de triangles représentant la salle de spectacle.
 *          Elle peut prendre en paramètre de création un fichier de définition de salle, ou un QJsonDocument
 *          représentant la salle.
 */
class SalleDeSpectacle : public QObject
{
    Q_OBJECT
public:
    explicit SalleDeSpectacle(QObject *parent = nullptr);
    SalleDeSpectacle(QString fileName, QObject *parent = nullptr);
    SalleDeSpectacle(QJsonDocument document, QObject *parent = nullptr);

    Triangle get_triangle(int trig);
    QList<Triangle> get_triangles();

    void set_triangle(Triangle trig, int pos);
    void set_filename(QString filename);
    void set_roomName(QString roomName);

    QJsonDocument get_JSON() const;
    QString get_roomName() const;
    QString get_filename() const;

signals:

public slots:
    void load();
    void load(QString filename);
    void load(QJsonDocument document);
    void save();
    void save(QString filename);

private:
    QList<Triangle> *border;
    QString filename;
    QString roomName;
};

#endif // SALLEDESPECTACLE_H
