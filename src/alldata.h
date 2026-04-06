#ifndef ALLDATA_H
#define ALLDATA_H

#include "h.h"

typedef struct Vertex
{
    glm::dvec3 position;
    glm::dvec3 color;
    glm::dvec2 texture;
}Vertex;

typedef struct Element
{
    glm::uvec3 triangle;
}Element;

class OurObject;
class AllData
{
public:
    AllData():vbo(QOpenGLBuffer::Type::VertexBuffer), ebo(QOpenGLBuffer::Type::IndexBuffer) {}
    ~AllData();
    void init(QOpenGLFunctions *f);
    void add_triangle(float x_1, float y_1, float x_2, float y_2, float x_3, float y_3, float r, float g, float b);
    void add_rectangle(float x_1, float y_1, float x_2, float y_2, float r, float g, float b);
    void add_cube(glm::dvec3 v1, glm::dvec3 v2, glm::dvec3 v3, glm::dvec3 color);


    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ebo;
    QOpenGLTexture *tex1;

    // std::vector<Vertex> vertices;
    // std::vector<Element> indices;
    // int count_obj;
    // std::vector<int> identify;
    std::vector<OurObject> object_l;
    // std::vector<glm::dvec3> models;
};

#endif // ALLDATA_H

