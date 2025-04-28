#include "scene.h"
#include <QJsonObject>
#include <QJsonArray>


/**
 * @brief Scene::Scene Constructeur de la classe Scene.
 * @param parent L'objet parent de l'objet créé. Ce paramètre est nul par défaut.
 */
Scene::Scene(QObject *parent)
    : QObject{parent}
{
    this->border = new QList<Triangle>();
    this->sceneName = QString();
    this->filename = QString();
}

/**
 * @brief Scene::Scene Constructeur de la classe Scene.
 * @param fileName l'adresse du fichier à charger pour initialiser la Scene.
 * @param parent L'objet parent de l'objet créé. Ce paramètre est nul par défaut.
 */
Scene::Scene(QString fileName, QObject *parent)
    : QObject{parent}
{
    //Initialisations
    this->border = new QList<Triangle>();
    this->load(fileName);
}

/**
 * @brief Scene::Scene Constructeur de la Scene.
 * @param document l'objet JSON à charger pour initialiser la Scene.
 * @param parent L'objet parent de l'objet créé. Ce paramètre est nul par défaut.
 */
Scene::Scene(QJsonDocument document, QObject *parent)
    : QObject{parent}
{
    //Initialisations
    this->border = new QList<Triangle>();
    this->filename = QString();

    this->load(document);
}


/**
 * @brief Scene::get_triangle Permet de récupérer un triangle de l'objet
 * @param trig numéro du triangle recherché
 * @return Renvoie la liste des points définissant les coordonnées 3D du triangle demandé.
 */
Triangle Scene::get_triangle(int trig)
{
    if(this->border->size() > trig)
        return this->border->at(trig);
    else
        return Triangle();
}


/**
 * @brief Scene::set_layer Permet de redéfinir un triangle de l'objet
 * @param trig Le nouveau triangle
 * @param pos l'identifiant du triangle à modifier.
 */
void Scene::set_triangle(Triangle trig, int pos)

{
    if(pos < this->border->size())
        this->border->replace(pos, trig);
    else
        qDebug() << QString("The required triangle (") << pos << QString(") isn't exist.");
}


/**
 * @brief Scene::load Permet de charger les informations de la classe dans le fichier préalablement défini.
 */
void Scene::load()
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
 * @brief Scene::load Permet de charger les informations de la scène en spécifiant le fichier à charger
 * @param filename le fichier à charger
 */
void Scene::load(QString filename)
{
    this->filename = filename;
    this->load();
}

/**
 * @brief Scene::load Permet de charger les informations de la scène en spécifiant directement un objet à charger
 * @param document le document JSON à traiter
 */
void Scene::load(QJsonDocument document)
{
    if(document.isObject()) //Ai-je bien une salle de spectacle
    {
        QJsonObject obj = document.object(); //Le tableau de points
        if(obj.contains("sceneName") && obj.value("sceneName").isString())
            this->sceneName = obj.value("sceneName").toString();

        if(obj.contains("scene") && obj.value("scene").isArray()) //Ai-je bien des triangles
        {
            QJsonArray all_triangles = obj.value("scene").toArray(); //Les triangles
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
 * @brief Scene::save Permet d'enregistrer les données de la scène dans le fichier inscrit dans l'objet
 */
void Scene::save()
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
 * @brief Scene::save Permet d'enregistrer les données de la scene dans le fichier fourni en paramètre
 * @param filename le nom du fichier pour l'enregistrement
 */
void Scene::save(QString filename)
{
    this->filename = filename;
    this->save();
}

/**
 * @brief Scene::get_JSON retourne un objet JSON représentant la scène
 * @return L'objet JSON représentant la scène
 */
QJsonDocument Scene::get_JSON()
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
    room.insert("scene",triangles);
    room.insert("sceneName",this->sceneName);

    QJsonDocument json;
    json.setObject(room);
    return json;
}

/**
 * @brief Scene::get_sceneName retourne le nom de la scène
 * @return Le nom de la scène
 */
QString Scene::get_sceneName() const
{
    return this->sceneName;
}

/**
 * @brief Scene::get_fileName retourne le chemin du fichier de la scène
 * @return Le chemin d'enregistrement du fichier de la scène
 */
QString Scene::get_filename() const
{
    return this->filename;
}

/**
 * @brief Scene::set_roomName Permet de définir le nom de la scène
 * @param Le nom de la scène
 */
void Scene::set_sceneName(QString sceneName)
{
    this->sceneName = sceneName;
}

/**
 * @brief Scene::set_fileName permet de définir le chemin du fichier de la scène
 * @param Le chemin d'enregistrement du fichier de la scène
 */
void Scene::set_filename(QString filename)
{
    this->filename = filename;
}
