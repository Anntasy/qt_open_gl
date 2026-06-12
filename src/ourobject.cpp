#include "ourobject.h"

OurObject::OurObject(QWidget* parent): QOpenGLWidget(parent)/*: vbo->(QOpenGLBuffer::Type::VertexBuffer), ebo(QOpenGLBuffer::Type::IndexBuffer)*/
{
    std::cout << "OurObject\n";
    vao = new QOpenGLVertexArrayObject();
    vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    ebo = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);
}

OurObject::~OurObject()
{
    vao->destroy();
    vbo->destroy();
    ebo->destroy();
    delete vao;
    delete vbo;
    delete ebo;
}

void OurObject::init(QOpenGLFunctions *f)
{
    // initializeOpenGLFunctions();
    makeCurrent();
    // for (int i=0; i<vertices.size(); i++)
    // {
    //     qDebug() << vertices[i].position << "\n";
    // }

    // for (int i=0; i<indices.size(); i++)
    // {
    //     qDebug() << indices[i].triangle[0] << " " << indices[i].triangle[1] << " " << indices[i].triangle[2] << "\n";
    // }

    vao->create();
    vao->bind();

    vbo->create();
    vbo->bind();
    vbo->allocate(vertices.constData(), vertices.size()*sizeof(Vertex));

    ebo->create();
    ebo->bind();
    ebo->allocate(indices.constData(), indices.size()*sizeof(Element));

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (GLvoid*) 0);

    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, false,
                             sizeof(Vertex), (GLvoid*) (sizeof(QVector3D)));


    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(2, 2, GL_FLOAT, false,
                             sizeof(Vertex), (GLvoid*) (2*sizeof(QVector3D)));

    vao->release();
    vbo->release();
    ebo->release();
    doneCurrent();
}
