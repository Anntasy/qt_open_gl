#ifndef OUROBJECT_H
#define OUROBJECT_H
#include "h.h"

struct Vertex;
struct Element;

class OurObject: public QOpenGLWidget
{
public:
    OurObject(QWidget* parent = nullptr);
    ~OurObject();
    // OurObject(void (*draw_f)(void));
    void init(QOpenGLFunctions *f);

    // QVector<QOpenGLTexture*> tex;
    QVector<Vertex> vertices;
    QVector<Element> indices;
    QVector3D model;

    QOpenGLVertexArrayObject *vao; //pointer
    QOpenGLBuffer *vbo;
    QOpenGLBuffer *ebo;
    // void (*draw)(void) = nullptr;
};

#endif // OUROBJECT_H
