#include "openglwidget.h"

// vertices (EBO)
/*float vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
};*/
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};

// indices
unsigned int indices[] = {
    0,1,2
};

// VAO, VBO, EBO
unsigned int VAO,VBO,EBO;



OpenGlWidget::OpenGlWidget(QWidget *parent): QOpenGLWidget(parent)
{

}

OpenGlWidget::~OpenGlWidget()
{
    makeCurrent();
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteVertexArrays(1,&VAO);
    doneCurrent();
}

void OpenGlWidget::drawShape(OpenGlWidget::Shape shape)
{
    m_shape = shape;

    // OpenGlWidget::patinGL()
    update();
}

void OpenGlWidget::setWireFrame(bool wireframe)
{
    makeCurrent();
    if(wireframe)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    // OpenGlWidget::paintGL()
    update();
    doneCurrent();
}

void OpenGlWidget::initializeGL()
{
    initializeOpenGLFunctions(); // GLAD

    // VAO， VBO
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

    glEnableVertexAttribArray(0);

    //shaderProgram.addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,vertexShaderSource);
    //shaderProgram.addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,fragmentShaderSource);
    bool success;
    shaderProgram.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,":shaders/shapes.vert");
    shaderProgram.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,":shaders/shapes.frag");
    success = shaderProgram.link();
    if(!success)
    {
        qDebug()<<"ERR:"<<shaderProgram.log();
    }


    // GL_FILE
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    // EBO
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    // GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void OpenGlWidget::resizeGL(int , int )
{

}

void OpenGlWidget::paintGL()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();

    glBindVertexArray(VAO);

    switch(m_shape){
    case Rect:glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
        break;
    default:
        break;
    }
}
