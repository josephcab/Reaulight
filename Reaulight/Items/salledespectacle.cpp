#include "salledespectacle.h"
#include <QJsonObject>
#include <QJsonArray>

SalleDeSpectacle::SalleDeSpectacle(QObject *parent)
    : QObject{parent}
{
    this->layers = new QList<QList<QVector3D>>();
}

SalleDeSpectacle::SalleDeSpectacle(QString fileName, QObject *parent)
    : QObject{parent}
{
    //Initialisations
    this->layers = new QList<QList<QVector3D>>();
    this->load(fileName);
}

QList<QVector3D> SalleDeSpectacle::get_ground() //Retourne la première couche, qui correspond au sol.
{
    return this->layers->first();
}

QList<QVector3D> SalleDeSpectacle::get_roof() //Retourne la dernière couche, qui représente le toit.
{
    return this->layers->last();
}

QList<QVector3D> SalleDeSpectacle::get_layer(int layer) //Retourne une couche spécifique si elle existe, sinon renvoie une liste vide.
{
    if(this->layers->size() > layer)
        return this->layers->at(layer);
    else
        return QList<QVector3D>();
}

void SalleDeSpectacle::set_ground(QList<QVector3D> ground_points) //Modifie la première couche (index 0), qui est le sol.
{
    this->layers->replace(0,ground_points);
}

void SalleDeSpectacle::set_roof(QList<QVector3D> roof_points) //Modifie la dernière couche, qui est le toit.
{
    this->layers->replace(this->layers->size()-1,roof_points);
}

void SalleDeSpectacle::set_layer(QList<QVector3D> layer_points, int layer) //Modifie une couche spécifique, mais affiche un message si elle n'existe pas.
{
    if(layer < this->layers->size())
        this->layers->replace(layer, layer_points);
    else
        qDebug() << QString("The required layer (") << layer << QString(") isn't exist.");
}



void SalleDeSpectacle::load()
{
    //Récupération du fichier JSON
    QFile data(this->filename);
    data.open(QIODevice::ReadWrite);
    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(QString::fromUtf8(data.readAll()).toUtf8(),&err);
    qDebug() << err.errorString();

    this->load(json);
    data.close();
}

void SalleDeSpectacle::load(QString filename)
{
    this->filename = filename;
    this->load();
}

void SalleDeSpectacle::load(QJsonDocument document)
{
    if(document.isObject()) //Ai-je bien une salle de spectacle
    {
        QJsonObject obj = document.object(); //Le tableau de points
        if(obj.contains("name") && obj.value("name").isString())
            this->roomName = obj.value("name").toString();

        if(obj.contains("layers") && obj.value("layers").isArray()) //Ai-je bien des couches de données
        {
            QJsonArray all_layer = obj.value("layers").toArray(); //Les couches de données
            for(int i = 0; i < all_layer.size();i++)
            {
                if(all_layer[i].isArray())
                {
                    QJsonArray layer = all_layer[i].toArray(); // la couche de donnée
                    QList<QVector3D> layer_data;
                    for(int j = 0; j < layer.size(); j++)
                    {
                        if(layer[j].isArray() && layer[j].toArray().size() == 3 &&
                            layer[j].toArray()[0].isDouble() &&
                            layer[j].toArray()[1].isDouble() &&
                            layer[j].toArray()[2].isDouble())
                        {
                            layer_data.append(QVector3D(layer[j].toArray()[0].toInt(),
                                                                    layer[j].toArray()[1].toInt(),
                                                                    layer[j].toArray()[2].toInt()));
                        }
                        else
                            qDebug() << QString("SalleDeSpectacle::load : Ceci n'est pas un nombre");
                    }
                    this->layers->append(layer_data);
                }
                else
                    qDebug() << QString("SalleDeSpectacle::load : Ceci n'est pas une scène valide - Il n'y a pas de couche horizontale.");
            }
        }
        else
            qDebug() << QString("SalleDeSpectacle::load : Ceci n'est pas une scène valide - Pas d'élément layers");

    }
    else
        qDebug() << QString("SalleDeSpectacle::load : Ceci n'est pas une scène valide");
}

void SalleDeSpectacle::save()
{
    QFile data(this->filename);
    data.open(QIODevice::WriteOnly);
    data.write(this->get_JSON().toJson());
    data.close();
}

void SalleDeSpectacle::save(QString filename)
{
    this->filename = filename;
    this->save();
}

QJsonDocument SalleDeSpectacle::get_JSON()
{
    QJsonArray layers;
    for(int i=0; i < this->layers->size(); i++)
    {
        qDebug() << this->layers->value(i).size();
        QJsonArray surface;
        for(int j=0; j < this->layers->value(i).size(); j++)
        {
            QJsonArray point;
            point.append(this->layers->at(i).at(j).x());
            point.append(this->layers->at(i).at(j).y());
            point.append(this->layers->at(i).at(j).z());
            surface.append(point);

            QJsonDocument test;
            test.setArray(point);
            qDebug() << test.toJson() << this->layers->value(i).value(j).x();
        }
        layers.append(surface);
    }

    QJsonObject room;
    room.insert("layers",layers);
    room.insert("name", this->roomName);

    QJsonDocument json;
    json.setObject(room);
    return json;
}
