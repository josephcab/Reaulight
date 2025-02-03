#ifndef SALLEDESPECTACLE_H
#define SALLEDESPECTACLE_H

#include <QObject>
#include <QList>
#include <QVector3D>
#include <QJsonDocument>
#include <QFile>


class SalleDeSpectacle : public QObject
{
    Q_OBJECT
public:
    explicit SalleDeSpectacle(QObject *parent = nullptr);
    SalleDeSpectacle(QString fileName, QObject *parent = nullptr);

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
