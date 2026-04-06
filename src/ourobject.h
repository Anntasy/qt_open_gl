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

    std::vector<QOpenGLTexture*> tex;
    std::vector<Vertex> vertices;
    std::vector<Element> indices;
    glm::dvec3 model;

    // void (*draw)(void) = nullptr;
};

#endif // OUROBJECT_H
