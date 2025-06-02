#include "structure.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

Structure::Structure(QObject *parent) : QObject{parent}
{
    this->name = "";
    this->filename = "";
    this->axes = QList<QPair<QVector3D, QVector3D> >();
}

Structure::Structure(QString fileName, QObject *parent) : QObject{parent}
{
    this->filename = fileName;
    load();
}

Structure::Structure(QJsonDocument document, QObject *parent): QObject{parent}
{
    this->axes = QList<QPair<QVector3D, QVector3D> >();
    load(document);
}

QString Structure::getName()
{
    return this->name;
}

unsigned int Structure::getDiameter()
{
    return this->diameter;
}

void Structure::setName(QString name)
{
    this->name = name;
}

void Structure::setAxes(QList<QPair<QVector3D, QVector3D> > axes)
{
    this->axes = axes;
}

void Structure::setAxe(unsigned int id, QVector3D start, QVector3D end)
{
    if(id < this->axes.length() && start != end)
    {
        this->axes[id] = QPair<QVector3D, QVector3D>(start, end);
    }
}

void Structure::setDiameter(unsigned int diameter)
{
    this->diameter = diameter;
}

void Structure::setAxe(unsigned int id, QPair<QVector3D, QVector3D> axe)
{
    if(id < this->axes.length() && axe.first != axe.second)
    {
        this->axes[id] = axe;
    }
}

QList<QPair<QVector3D, QVector3D> > Structure::getAxes()
{
    return this->axes;
}

QPair<QVector3D, QVector3D> Structure::getAxe(unsigned int id)
{
    if(id < this->axes.length())
    {
        return this->axes[id];
    }
}

QJsonDocument Structure::getJSON() const
{
    QJsonArray axes = QJsonArray();
    for (int i = 0; i < this->axes.length(); i++)
    {
        QJsonObject axe = QJsonObject();
        QJsonObject start = QJsonObject();
        start.insert("x", this->axes[i].first.x());
        start.insert("y", this->axes[i].first.y());
        start.insert("z", this->axes[i].first.z());
        axe.insert("start",start);

        QJsonObject end = QJsonObject();
        end.insert("x", this->axes[i].second.x());
        end.insert("y", this->axes[i].second.y());
        end.insert("z", this->axes[i].second.z());
        axe.insert("end",end);

        axes.append(axe);
    }

    QJsonObject structure;
    structure.insert("type","Structure");
    structure.insert("name", this->name);
    structure.insert("diameter", (int)this->diameter);
    structure.insert("axes", axes);

    QJsonDocument json;
    json.setObject(structure);
    return json;
}

QString Structure::getFilename() const
{
    return this->filename;
}

void Structure::load()
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

void Structure::load(QString filename)
{
    this->filename = filename;
    this->load();
}

void Structure::load(QJsonDocument document)
{
    if(document.isObject() && document.object().contains("type") && document.object().value("type") == "structure") //Ai-je bien une structure
    {
        QJsonObject obj = document.object(); // La structure

        if(obj.contains("name") && obj.value("name").isString())
            this->name = obj.value("name").toString();

        if(obj.contains("diameter") && obj.value("diameter").isDouble())
            this->diameter = obj.value("diameter").toInt();

        if(obj.contains("axes") && obj.value("axes").isArray())
        {
            QJsonArray axes = obj.value("axes").toArray();
            for(int i = 0; i < axes.size(); i++)
            {
                if(axes.at(i).isObject() && axes.at(i).toObject().contains("start") && axes.at(i).toObject().contains("end"))
                {
                    QJsonObject start = axes.at(i).toObject().value("start").toObject();
                    QJsonObject end = axes.at(i).toObject().value("end").toObject();

                    if( start.contains("x") && start.value("x").isDouble() && end.contains("x") && end.value("x").isDouble() &&
                        start.contains("y") && start.value("y").isDouble() && end.contains("y") && end.value("y").isDouble() &&
                        start.contains("z") && start.value("z").isDouble() && end.contains("z") && end.value("z").isDouble() )
                    {
                        this->axes.append(QPair<QVector3D, QVector3D>(QVector3D(start.value("x").toInt(),start.value("y").toInt(),start.value("z").toInt()),
                                                                      QVector3D(end.value("x").toInt(),end.value("y").toInt(),end.value("z").toInt())));
                    }
                }
            }
        }
    }
}

void Structure::save()
{
    QFile data(this->filename);
    if(data.open(QIODevice::WriteOnly))
    {
        data.write(this->getJSON().toJson());
        data.close();
    }
    else
        qDebug() << QString("Impossible d'ouvrir le ficher");
}


void Structure::save(QString filename)
{
    this->filename = filename;
    this->save();
}
