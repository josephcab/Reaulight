#ifndef TRIANGLE
#define TRIANGLE

#include <QObject>
#include <QVector3D>

/**
     * @brief La classe Triangle
     * @details La classe Triangle permet d'instancier un triangle (sous forme de 3 points)
     */
class Triangle// : public QObject
{
     //Q_OBJECT
public:
    explicit Triangle();
    Triangle(QVector3D a, QVector3D b, QVector3D c);

    void setPoint(int id, QVector3D point);
    void setTriangle(QVector3D point[3]);

    QVector3D getPoint(int id) const;

private:
    QVector3D triangle[3];

};

#endif // TRIANGLE
