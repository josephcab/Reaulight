#include "salledespectacle.h"
#include <QJsonObject>
#include <QJsonArray>


/**
 * @brief SalleDeSpectacle::SalleDeSpectacle Constructeur de la classe Salle de Spectacle.
 * @param parent L'objet parent de l'objet créé. Ce paramètre est nul par défaut.
 */
SalleDeSpectacle::SalleDeSpectacle(QObject *parent)
    : QObject{parent}
{
    this->layers = new QList<QList<QVector3D>>();
}

/**
 * @brief SalleDeSpectacle::SalleDeSpectacle Constructeur de la classe Salle de Spectacle.
 * @param fileName l'adresse du fichier à charger pour initialiser la SalleDeSpectacle.
 * @param parent L'objet parent de l'objet créé. Ce paramètre est nul par défaut.
 */
SalleDeSpectacle::SalleDeSpectacle(QString fileName, QObject *parent)
    : QObject{parent}
{
    //Initialisations
    this->layers = new QList<QList<QVector3D>>();
    this->load(fileName);
}

/**
 * @brief SalleDeSpectacle::SalleDeSpectacle Constructeur de la classe Salle de Spectacle.
 * @param document l'objet JSON à charger pour initialiser la SalleDeSpectacle.
 * @param parent L'objet parent de l'objet créé. Ce paramètre est nul par défaut.
 */
SalleDeSpectacle::SalleDeSpectacle(QJsonDocument document, QObject *parent)
    : QObject{parent}
{
    //Initialisations
    this->layers = new QList<QList<QVector3D>>();
    this->filename = QString();

    this->load(document);
}

/**
 * @brief SalleDeSpectacle::get_ground Permet de récupérer la liste de points représentant la salle de spectacle.
 * @return Une liste ordonnée de points représentant les coordonnées 3D des points du sol.
 */
QList<QVector3D> SalleDeSpectacle::get_ground()
{
    return this->layers->first();
}

/**
 * @brief SalleDeSpectacle::get_roof retourne la liste des points définissant le plafond de la salle.
 * @return retourne la liste des points définissant les coordonnées 3D des points du plafond.
 */
QList<QVector3D> SalleDeSpectacle::get_roof()
{
    return this->layers->last();
}

/**
 * @brief SalleDeSpectacle::get_layer Renvoie le contenu d'une couche  de construction de la salle
 * @param layer numéro de la couche recherchée
 * @return Renvoie la liste des points définissant les coordonnées 3D des points de la couche demandée.
 */
QList<QVector3D> SalleDeSpectacle::get_layer(int layer)
{
    if(this->layers->size() > layer)
        return this->layers->at(layer);
    else
        return QList<QVector3D>();
}

/**
 * @brief SalleDeSpectacle::set_ground Permet de redéfinir la liste des points du sol
 * @param ground_points La liste des points 3D du sol
 */
void SalleDeSpectacle::set_ground(QList<QVector3D> ground_points)
{
    this->layers->replace(0,ground_points);
}

/**
 * @brief SalleDeSpectacle::set_roof Permet de redéfinir la liste des points du plafond
 * @param roof_points La liste des points 3D du plafond
 */
void SalleDeSpectacle::set_roof(QList<QVector3D> roof_points)
{
    this->layers->replace(this->layers->size()-1,roof_points);
}

/**
 * @brief SalleDeSpectacle::set_layer Permet de redéfinir la liste des points d'une couche de données
 * @param layer_points La liste des points 3D de la couche en question
 * @param layer la couche à modifier
 */
void SalleDeSpectacle::set_layer(QList<QVector3D> layer_points, int layer)

{
    if(layer < this->layers->size())
        this->layers->replace(layer, layer_points);
    else
        qDebug() << QString("The required layer (") << layer << QString(") isn't exist.");
}


/**
 * @brief SalleDeSpectacle::load Permet de charger les informations de la classe dans le fichier préalablement défini.
 */
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

/**
 * @brief SalleDeSpectacle::load Permet de charger les informations de la salle de spectacle en spécifiant le fichier à charger
 * @param filename le fichier à charger
 */
void SalleDeSpectacle::load(QString filename)
{
    this->filename = filename;
    this->load();
}

/**
 * @brief SalleDeSpectacle::load Permet de charger les informations de la salle de spectacle en spécifiant directement un objet à charger
 * @param document le document JSON à traiter
 */
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

/**
 * @brief SalleDeSpectacle::save Permet d'enregistrer les données de la salle de spectacle dans le fichier inscrit dans l'objet
 */
void SalleDeSpectacle::save()
{
    QFile data(this->filename);
    if(data.open(QIODevice::WriteOnly))
    {
        data.write(this->get_JSON().toJson());
        data.close();
    }
    else
        qDebug() << QString("Impossible d'ouvrir le ficher");
}

/**
 * @brief SalleDeSpectacle::save Permet d'enregistrer les données de la salle de spectacle dans le fichier fourni en paramètre
 * @param filename le nom du fichier pour l'enregistrement
 */
void SalleDeSpectacle::save(QString filename)
{
    this->filename = filename;
    this->save();
}

/**
 * @brief SalleDeSpectacle::get_JSON retourne un objet JSON représentant la salle de spectacle
 * @return L'objet JSON représentant la salle de spectacle
 */
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
