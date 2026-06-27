#ifndef ALLDATA_H
#define ALLDATA_H

#include "h.h"

typedef struct Vertex
{
    QVector3D position;
    QVector3D color;
    QVector2D texture;
}Vertex;

typedef struct Element
{
    glm::uvec3 triangle;
}Element;

class OurObject;
class AllData
{
public:
    AllData();
    ~AllData();
    void init(QOpenGLFunctions *f);
    void add_triangle(float x_1, float y_1, float x_2, float y_2, float x_3, float y_3, float r, float g, float b);
    void add_rectangle(float x_1, float y_1, float x_2, float y_2, float r, float g, float b);
    void add_cube(QVector3D v1, QVector3D v2, QVector3D v3, QVector3D color);
    void add_model(std::string path);

    // QOpenGLVertexArrayObject vao;
    // QOpenGLBuffer vbo;
    // QOpenGLBuffer ebo;
    QOpenGLTexture *tex1;

    // std::vector<Vertex> vertices;
    // std::vector<Element> indices;
    // int count_obj;
    // std::vector<int> identify;

    std::vector<OurObject *> object_l;

    // std::vector<QVector3D> models;
};

#endif // ALLDATA_H

