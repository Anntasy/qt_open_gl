#include "alldata.h"


AllData::~AllData()
{
    delete tex1;
    vao.destroy();
    vbo.destroy();
    ebo.destroy();
}

void AllData::init(QOpenGLFunctions *f)
{
    std::vector<Vertex> vertices_b;
    std::vector<Element> indices_b;

    for (auto object: object_l)
    {
        vertices_b.insert(vertices_b.end(), object.vertices.begin(), object.vertices.end());
        indices_b.insert(indices_b.end(), object.indices.begin(), object.indices.end());
    }

    QVector<Vertex> vertices (vertices_b.begin(), vertices_b.end());
    QVector<Element> indices (indices_b.begin(), indices_b.end());

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices.constData(), vertices.size()*sizeof(Vertex));

    ebo.create();
    ebo.bind();
    ebo.allocate(indices.constData(), indices.size()*sizeof(Element));

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (GLvoid*) 0);


    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, false,
                           sizeof(Vertex), (GLvoid*) (sizeof(QVector3D)));


    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(2, 2, GL_FLOAT, false,
                           sizeof(Vertex), (GLvoid*) (2*sizeof(QVector3D)));

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
    OurObject object;
    object_l.push_back(object);
    int size_l = object_l.size()-1;

    object_l[size_l].vertices.push_back({{0, 0, 0}, {r, g, b}, {0, 0}});
    object_l[size_l].vertices.push_back({{x_2, y_2, 0}, {r, g, b}, {0.5, 1}});
    object_l[size_l].vertices.push_back({{x_3, y_3, 0}, {r, g, b}, {1, 0}});

    object_l[size_l].indices.push_back({{object_l[size_l].vertices.size()-3, object_l[size_l].vertices.size()-2, object_l[size_l].vertices.size()-1}});

    object_l[size_l].model = QVector3D(x_1, y_1, 0);
}


void AllData::add_rectangle(float x_1, float y_1, float x_2, float y_2, float r, float g, float b)
{
    OurObject object;
    int size_l = object_l.size()-1;
    object_l.push_back(object);

    x_2 -= x_1;
    y_2 -= y_1;

    object_l[size_l].vertices.push_back({{0, 0, 0}, {r, g, b}, {0, 0}});
    object_l[size_l].vertices.push_back({{0, y_2, 0}, {r, g, b}, {0, 1}});
    object_l[size_l].vertices.push_back({{x_2, y_2, 0}, {r, g, b}, {1, 1}});
    object_l[size_l].vertices.push_back({{x_2, 0, 0}, {r, g, b}, {1, 0}});

    auto vertices = &object_l[size_l].vertices;

    object_l[size_l].indices.push_back({{vertices->size()-4, vertices->size()-3, vertices->size()-2}});
    object_l[size_l].indices.push_back({{vertices->size()-1, vertices->size()-4, vertices->size()-2}});

    object_l[size_l].model = QVector3D(x_1, y_1, 0);
}


void AllData::add_cube(QVector3D v1, QVector3D v2, QVector3D v3, QVector3D color)
{
    OurObject object;
    int size_l = object_l.size()-1;
    object_l.push_back(object);

    QVector3D copy_v1 = v1;
    v2 -= v1;
    v3 -= v1;
    v1 -= v1;

    object_l[size_l].vertices.push_back({v1, color, {0, 1}});
    object_l[size_l].vertices.push_back({v2, color, {1, 1}});
    object_l[size_l].vertices.push_back({v3, color, {1, 0}});

    QVector3D a = v3 - v2 ;
    object_l[size_l].vertices.push_back({v1 + a, color, {0, 0}});

    QVector3D b = v1 - v2 ;
    QVector3D c = QVector3D::crossProduct(b, a) * (1/a.length());

    object_l[size_l].vertices.push_back({v1 + a + c, color, {1, 0}});
    object_l[size_l].vertices.push_back({v3 + c, color, {0, 0}});
    object_l[size_l].vertices.push_back({v2 + c, color, {0, 1}});
    object_l[size_l].vertices.push_back({v1 + c, color, {1, 1}});

    // replace repeating coord
    object_l[size_l].vertices.push_back({v1 + a + c, color, {0, 1}});
    object_l[size_l].vertices.push_back({v3 + c, color, {1, 1}});
    object_l[size_l].vertices.push_back({v2 + c, color, {1, 0}});
    object_l[size_l].vertices.push_back({v1 + c, color, {0, 0}});

    auto vertices = &object_l[size_l].vertices;

    object_l[size_l].indices.push_back({{vertices->size()-12, vertices->size()-11, vertices->size()-10}});
    object_l[size_l].indices.push_back({{vertices->size()-10, vertices->size()-9, vertices->size()-12}});

    object_l[size_l].indices.push_back({{vertices->size()-12, vertices->size()-9, vertices->size()-8}});
    object_l[size_l].indices.push_back({{vertices->size()-8, vertices->size()-5, vertices->size()-12}});

    object_l[size_l].indices.push_back({{vertices->size()-5, vertices->size()-8, vertices->size()-7}});
    object_l[size_l].indices.push_back({{vertices->size()-7, vertices->size()-6, vertices->size()-5}});

    object_l[size_l].indices.push_back({{vertices->size()-7, vertices->size()-6, vertices->size()-11}});
    object_l[size_l].indices.push_back({{vertices->size()-11, vertices->size()-10, vertices->size()-7}});


    object_l[size_l].indices.push_back({{vertices->size()-12, vertices->size()-1, vertices->size()-2}});
    object_l[size_l].indices.push_back({{vertices->size()-2, vertices->size()-11, vertices->size()-12}});

    object_l[size_l].indices.push_back({{vertices->size()-9, vertices->size()-4, vertices->size()-3}});
    object_l[size_l].indices.push_back({{vertices->size()-3, vertices->size()-10, vertices->size()-9}});

    object_l[size_l].model = copy_v1;
}
