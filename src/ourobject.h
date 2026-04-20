#ifndef OUROBJECT_H
#define OUROBJECT_H
#include "h.h"

struct Vertex;
struct Element;

class OurObject
{
public:
    OurObject();
    // OurObject(void (*draw_f)(void));

    QVector<QOpenGLTexture*> tex;
    QVector<Vertex> vertices;
    QVector<Element> indices;
    QVector3D model;

    // void (*draw)(void) = nullptr;
};

#endif // OUROBJECT_H
