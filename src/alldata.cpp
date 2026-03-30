#include "alldata.h"


AllData::~AllData()
{
    delete tex1;
}

void AllData::init(QOpenGLFunctions *f)
{
    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices.data(), vertices.size()*sizeof(Vertex));

    ebo.create();
    ebo.bind();
    ebo.allocate(indices.data(), indices.size()*sizeof(Element));

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_DOUBLE, false, sizeof(Vertex), (GLvoid*) 0);


    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1, 3, GL_DOUBLE, false,
                           sizeof(Vertex), (GLvoid*) (3*sizeof(glm::float64)));


    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(2, 2, GL_DOUBLE, false,
                           sizeof(Vertex), (GLvoid*) (6*sizeof(glm::float64)));

    vao.release();
    vbo.release();
    ebo.release();

    QImage q_image(":/textures/wall.png");
    q_image = q_image.convertToFormat(QImage::Format_RGBA8888);
    tex1 = new QOpenGLTexture(QOpenGLTexture::Target2D);
    tex1->create();
    tex1->bind();
    tex1->setFormat(QOpenGLTexture::RGBA8_UNorm);
    tex1->setSize(q_image.width(), q_image.height());
    tex1->allocateStorage();

    tex1->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    tex1->setMagnificationFilter(QOpenGLTexture::Linear);
    tex1->setWrapMode(QOpenGLTexture::Repeat);
    tex1->setData(QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, q_image.constBits());
    tex1->generateMipMaps();
    tex1->release();
}

void AllData::add_triangle(float x_1, float y_1, float x_2, float y_2, float x_3, float y_3, float r, float g, float b)
{
    vertices.push_back({{0, 0, 0}, {r, g, b}, {0, 0}});
    vertices.push_back({{x_2, y_2, 0}, {r, g, b}, {0.5, 1}});
    vertices.push_back({{x_3, y_3, 0}, {r, g, b}, {1, 0}});

    indices.push_back({{vertices.size()-3, vertices.size()-2, vertices.size()-1}});

    count_obj++;
    identify.push_back(1);
    models.push_back(glm::dvec3(x_1, y_1, 0));
}


void AllData::add_rectangle(float x_1, float y_1, float x_2, float y_2, float r, float g, float b)
{
    x_2 -= x_1;
    y_2 -= y_1;

    vertices.push_back({{0, 0, 0}, {r, g, b}, {0, 0}});
    vertices.push_back({{0, y_2, 0}, {r, g, b}, {0, 1}});
    vertices.push_back({{x_2, y_2, 0}, {r, g, b}, {1, 1}});
    vertices.push_back({{x_2, 0, 0}, {r, g, b}, {1, 0}});

    indices.push_back({{vertices.size()-4, vertices.size()-3, vertices.size()-2}});
    indices.push_back({{vertices.size()-1, vertices.size()-4, vertices.size()-2}});

    count_obj++;
    identify.push_back(2);
    models.push_back(glm::dvec3(x_1, y_1, 0));
}


void AllData::add_cube(glm::dvec3 v1, glm::dvec3 v2, glm::dvec3 v3, glm::dvec3 color)
{
    glm::dvec3 copy_v1 = v1;
    v2 -= v1;
    v3 -= v1;
    v1 -= v1;

    vertices.push_back({v1, color, {0, 1}});
    vertices.push_back({v2, color, {1, 1}});
    vertices.push_back({v3, color, {1, 0}});

    glm::dvec3 a = v3 - v2 ;
    vertices.push_back({v1 + a, color, {0, 0}});

    glm::dvec3 b = v1 - v2 ;
    glm::dvec3 c = glm::cross(b, a) * (1/glm::length(a));

    vertices.push_back({v1 + a + c, color, {1, 0}});
    vertices.push_back({v3 + c, color, {0, 0}});
    vertices.push_back({v2 + c, color, {0, 1}});
    vertices.push_back({v1 + c, color, {1, 1}});

    // replace repeating coord
    vertices.push_back({v1 + a + c, color, {0, 1}});
    vertices.push_back({v3 + c, color, {1, 1}});
    vertices.push_back({v2 + c, color, {1, 0}});
    vertices.push_back({v1 + c, color, {0, 0}});


    indices.push_back({{vertices.size()-12, vertices.size()-11, vertices.size()-10}});
    indices.push_back({{vertices.size()-10, vertices.size()-9, vertices.size()-12}});

    indices.push_back({{vertices.size()-12, vertices.size()-9, vertices.size()-8}});
    indices.push_back({{vertices.size()-8, vertices.size()-5, vertices.size()-12}});

    indices.push_back({{vertices.size()-5, vertices.size()-8, vertices.size()-7}});
    indices.push_back({{vertices.size()-7, vertices.size()-6, vertices.size()-5}});

    indices.push_back({{vertices.size()-7, vertices.size()-6, vertices.size()-11}});
    indices.push_back({{vertices.size()-11, vertices.size()-10, vertices.size()-7}});


    indices.push_back({{vertices.size()-12, vertices.size()-1, vertices.size()-2}});
    indices.push_back({{vertices.size()-2, vertices.size()-11, vertices.size()-12}});

    indices.push_back({{vertices.size()-9, vertices.size()-4, vertices.size()-3}});
    indices.push_back({{vertices.size()-3, vertices.size()-10, vertices.size()-9}});

    count_obj++;
    identify.push_back(12);
    models.push_back(copy_v1);
}
