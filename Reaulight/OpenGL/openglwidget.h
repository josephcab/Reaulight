#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include<QtOpenGLWidgets/QOpenGLWidget>
#include<QtOpenGL/QOpenGLFunctions_4_5_Core>
#include<QDebug>
#include<QOpenGLShaderProgram>

class OpenGlWidget : public QOpenGLWidget,QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    enum Shape{None,Rect,Circle,Triangle};
    explicit OpenGlWidget(QWidget *parent = nullptr);
    ~OpenGlWidget();

    // draws a shape
    void drawShape(Shape shape);
    // set frame wire
    void setWireFrame(bool wireframe);
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

signals:
private:
    Shape m_shape;
    QOpenGLShaderProgram shaderProgram;
};

#endif // OPENGLWIDGET_H
