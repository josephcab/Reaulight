#ifndef SALLEDESPECTACLE_H
#define SALLEDESPECTACLE_H

#include <QObject>
#include <QList>
#include <QVector3D>
#include <QJsonDocument>
#include <QFile>

/**
 * @brief The SalleDeSpectacle class
 * @details La classe SalleDeSpectacle est un classe permettant de représenter une salle de spectacle.
 *          Pour ce faire, elle définit au moins deux couches de points (sol et plafond).
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

    QList<QVector3D> get_ground();
    QList<QVector3D> get_roof();
    QList<QVector3D> get_layer(int layer);

    void set_ground(QList<QVector3D> ground_points);
    void set_roof(QList<QVector3D> roof_points);
    void set_layer(QList<QVector3D> layer_points, int layer);

    QJsonDocument get_JSON();

signals:

public slots:
    void load();
    void load(QString filename);
    void load(QJsonDocument document);
    void save();
    void save(QString filename);

private:
    QList<QList<QVector3D>> *layers;
    QString filename;
    QString roomName;
};

#endif // SALLEDESPECTACLE_H
