#ifndef TRIANGLE
#define TRIANGLE

#include <QObject>
#include <QVector3D>

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
