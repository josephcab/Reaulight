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
    this->border = new QList<Triangle>();
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
    this->border = new QList<Triangle>();
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
    this->border = new QList<Triangle>();
    this->filename = QString();

    this->load(document);
}


/**
 * @brief SalleDeSpectacle::get_layer Renvoie le contenu d'une couche  de construction de la salle
 * @param trig numéro du triangle recherché
 * @return Renvoie la liste des points définissant les coordonnées 3D des points de la couche demandée.
 */
Triangle SalleDeSpectacle::get_triangle(int trig)
{
    if(this->border->size() > trig)
        return this->border->at(trig);
    else
        return Triangle();
}


/**
 * @brief SalleDeSpectacle::set_layer Permet de redéfinir la liste des points d'une couche de données
 * @param layer_points La liste des points 3D de la couche en question
 * @param layer la couche à modifier
 */
void SalleDeSpectacle::set_triangle(Triangle trig, int pos)

{
    if(pos < this->border->size())
        this->border->replace(pos, trig);
    else
        qDebug() << QString("The required layer (") << pos << QString(") isn't exist.");
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

        if(obj.contains("triangles") && obj.value("triangles").isArray()) //Ai-je bien des triangles
        {
            QJsonArray all_triangles = obj.value("triangles").toArray(); //Les triangles
            for(int i = 0; i < all_triangles.size();i++)
            {
                if(all_triangles[i].isArray())
                {
                    QJsonArray triangle = all_triangles[i].toArray(); // le triangle
                    QList<QVector3D> points;
                    for(int j = 0; j < triangle.size(); j++)
                    {
                        if(triangle[j].isArray() && triangle[j].toArray().size() == 3 &&
                            triangle[j].toArray()[0].isDouble() &&
                            triangle[j].toArray()[1].isDouble() &&
                            triangle[j].toArray()[2].isDouble())
                        {
                            points.append(QVector3D(triangle[j].toArray()[0].toInt(),
                                                                    triangle[j].toArray()[1].toInt(),
                                                                    triangle[j].toArray()[2].toInt()));
                        }
                        else
                            qDebug() << QString("SalleDeSpectacle::load : Ceci n'est pas un nombre");
                    }
                    this->border->append(Triangle(points[0], points[1], points[2]));
                }
                else
                    qDebug() << QString("SalleDeSpectacle::load : Ceci n'est pas une scène valide - Il n'y a pas de points.");
            }
        }
        else
            qDebug() << QString("SalleDeSpectacle::load : Ceci n'est pas une scène valide - Pas de triangles");

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
    QJsonArray triangles;
    for(int i=0; i < this->border->size(); i++)
    {
        QJsonArray triangle;
        for(int j=0; j < 3; j++)
        {
            QJsonArray point;
            point.append(this->border->at(i).getPoint(j).x());
            point.append(this->border->at(i).getPoint(j).y());
            point.append(this->border->at(i).getPoint(j).z());
            triangle.append(point);

        }
        triangles.append(triangle);
    }

    QJsonObject room;
    room.insert("layers",triangles);
    room.insert("name", this->roomName);

    QJsonDocument json;
    json.setObject(room);
    return json;
}
