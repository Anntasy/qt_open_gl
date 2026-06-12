#include "alldata.h"
#include "h.h"


AllData::AllData()
{
    std::cout << "allData\n";
}

AllData::~AllData()
{
    for (std::size_t i=0; i<object_l.size(); i++)
    {
        delete object_l[i];
    }
    delete tex1;
    // vao.destroy();
    // vbo.destroy();
    // ebo.destroy();
}

void AllData::init(QOpenGLFunctions *f)
{
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


    for (int i=0; i<object_l.size(); i++)
    {
        // object_l[i].vao->bind();
        object_l[i]->init(f);

    }
}

void AllData::add_triangle(float x_1, float y_1, float x_2, float y_2, float x_3, float y_3, float r, float g, float b)
{
    OurObject *object;
    object = new OurObject();
    object_l.push_back(object);
    int size_l = object_l.size()-1;

    x_2 -= x_1;
    y_2 -= y_1;
    x_3 -= x_1;
    y_3 -= y_1;

    object_l[size_l]->vertices.push_back({{0, 0, 0}, {r, g, b}, {0, 0}});
    object_l[size_l]->vertices.push_back({{x_2, y_2, 0}, {r, g, b}, {0.5, 1}});
    object_l[size_l]->vertices.push_back({{x_3, y_3, 0}, {r, g, b}, {1, 0}});

    // object_l[size_l]->indices.push_back({{object_l[size_l]->vertices.size()-3, object_l[size_l]->vertices.size()-2, object_l[size_l]->vertices.size()-1}});
    object_l[size_l]->indices.push_back({{0, 1, 2}});

    object_l[size_l]->model = QVector3D(x_1, y_1, 0);
}


void AllData::add_rectangle(float x_1, float y_1, float x_2, float y_2, float r, float g, float b)
{
    OurObject *object;
    object = new OurObject();
    object_l.push_back(object);
    int size_l = object_l.size()-1;

    x_2 -= x_1;
    y_2 -= y_1;

    object_l[size_l]->vertices.push_back({{0, 0, 0}, {r, g, b}, {0, 0}});
    object_l[size_l]->vertices.push_back({{0, y_2, 0}, {r, g, b}, {0, 1}});
    object_l[size_l]->vertices.push_back({{x_2, y_2, 0}, {r, g, b}, {1, 1}});
    object_l[size_l]->vertices.push_back({{x_2, 0, 0}, {r, g, b}, {1, 0}});

    auto vertices = &object_l[size_l]->vertices;

    object_l[size_l]->indices.push_back({{vertices->size()-4, vertices->size()-3, vertices->size()-2}});
    object_l[size_l]->indices.push_back({{vertices->size()-1, vertices->size()-4, vertices->size()-2}});

    object_l[size_l]->model = QVector3D(x_1, y_1, 0);
}


void AllData::add_cube(QVector3D v1, QVector3D v2, QVector3D v3, QVector3D color)
{
    OurObject *object;
    object = new OurObject();
    object_l.push_back(object);
    int size_l = object_l.size()-1;

    QVector3D copy_v1 = v1;
    v2 -= v1;
    v3 -= v1;
    v1 -= v1;

    object_l[size_l]->vertices.push_back({v1, color, {0, 1}});
    object_l[size_l]->vertices.push_back({v2, color, {1, 1}});
    object_l[size_l]->vertices.push_back({v3, color, {1, 0}});

    QVector3D a = v3 - v2 ;
    object_l[size_l]->vertices.push_back({v1 + a, color, {0, 0}});

    QVector3D b = v1 - v2 ;
    QVector3D c = QVector3D::crossProduct(b, a) * (1/a.length());

    object_l[size_l]->vertices.push_back({v1 + a + c, color, {1, 0}});
    object_l[size_l]->vertices.push_back({v3 + c, color, {0, 0}});
    object_l[size_l]->vertices.push_back({v2 + c, color, {0, 1}});
    object_l[size_l]->vertices.push_back({v1 + c, color, {1, 1}});

    // replace repeating coord
    object_l[size_l]->vertices.push_back({v1 + a + c, color, {0, 1}});
    object_l[size_l]->vertices.push_back({v3 + c, color, {1, 1}});
    object_l[size_l]->vertices.push_back({v2 + c, color, {1, 0}});
    object_l[size_l]->vertices.push_back({v1 + c, color, {0, 0}});

    auto vertices = &object_l[size_l]->vertices;

    object_l[size_l]->indices.push_back({{vertices->size()-12, vertices->size()-11, vertices->size()-10}});
    object_l[size_l]->indices.push_back({{vertices->size()-10, vertices->size()-9, vertices->size()-12}});

    object_l[size_l]->indices.push_back({{vertices->size()-12, vertices->size()-9, vertices->size()-8}});
    object_l[size_l]->indices.push_back({{vertices->size()-8, vertices->size()-5, vertices->size()-12}});

    object_l[size_l]->indices.push_back({{vertices->size()-5, vertices->size()-8, vertices->size()-7}});
    object_l[size_l]->indices.push_back({{vertices->size()-7, vertices->size()-6, vertices->size()-5}});

    object_l[size_l]->indices.push_back({{vertices->size()-7, vertices->size()-6, vertices->size()-11}});
    object_l[size_l]->indices.push_back({{vertices->size()-11, vertices->size()-10, vertices->size()-7}});


    object_l[size_l]->indices.push_back({{vertices->size()-12, vertices->size()-1, vertices->size()-2}});
    object_l[size_l]->indices.push_back({{vertices->size()-2, vertices->size()-11, vertices->size()-12}});

    object_l[size_l]->indices.push_back({{vertices->size()-9, vertices->size()-4, vertices->size()-3}});
    object_l[size_l]->indices.push_back({{vertices->size()-3, vertices->size()-10, vertices->size()-9}});

    object_l[size_l]->model = copy_v1;
}


void AllData::add_model(std::string path)
{
    LoadModel l;
    l.get_info(path);
    OurObject *object;
    object = l.fill_info();
    object_l.push_back(object);

    /*
    object = new OurObject();
    object_l.push_back(object);*/

    // L argss
    // std::set<std::pair<int, int>> f_pos_tex_set;
    // std::vector<std::vector<int>> polygons;

    //  our  obj argss
    // QVector<Vertex> vertices; // vertices.push_back();
    // QVector<Element> indices;
    // QVector3D model;
}


OurObject * LoadModel::fill_info()
{
    OurObject *object;
    object = new OurObject;

    for (auto p: f_pos_tex_set)
    {
        Vertex v;
        v.position = v_pos[p.first];
        v.texture = v_tex[p.second];
        v.color = {0.1f, 0.2f, 0.3f};

        object->vertices.push_back(v);
    }


    for (auto poly: polygons)
    {
        Element e1 = {{poly[0], poly[1], poly[2]}};
        Element e2 = {{poly[0], poly[2], poly[3]}};
        object->indices.push_back(e1);
        object->indices.push_back(e2);
    }

    return object;
}

void LoadModel::get_info(const std::string path)
{
    std::ifstream file(path);

    std::string line;
    std::string number;
    double x;

    // QVector<QVector3D> v_pos;
    // QVector<QVector2D> v_tex;
    // std::set<std::pair<int, int>> f_pos_tex_set;
    // QVector<glm::uvec3> polygons;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        if (!(line.find("v ")) or !(line.find("vt")))
        {
            std::vector<double> cur_v_smth;
            while (ss >> number)
            {
                try {
                    std::size_t pos;
                    x = std::stod(number, &pos);
                    // if (pos > 0)
                    // std::cout << x << " | ";
                    cur_v_smth.push_back(x);
                }
                catch (...) {
                    continue;
                }
            }
            if (!(line.find("v ")))
            {
                // cur_v_smth => QVector3D
                QVector3D q_v_3(cur_v_smth[0], cur_v_smth[1], cur_v_smth[2]);
                v_pos.push_back(q_v_3);
            }

            else if (!(line.find("vt")))
            {
                // cur_v_smth => QVector2D
                QVector2D q_v_2(cur_v_smth[0], cur_v_smth[1]);
                v_tex.push_back(q_v_2);
            }
            // std::cout << " \n";
        }

        else if (!(line.find("f")))
        {
            line = line.substr(2);
            std::stringstream ss(line);
            std::string x;
            QVector<int> cur_f_pos;
            while (std::getline(ss, x, ' '))
            {
                std::stringstream s2(x);
                std::string y;
                int x1;
                int x2;

                try {
                    std::getline(s2, y, '/');
                    x1 = std::stoi(y);
                    std::getline(s2, y, '/');
                    x2 = std::stoi(y);
                }
                catch (...) {
                    continue;
                }

                std::pair<int, int> p = {x1, x2};
                f_pos_tex_set.insert(p);
                cur_f_pos.push_back(x1);
            }
            polygons.append(cur_f_pos);
        }
    }
    file.close();
}

// void LoadModel::show_all()
// {
//     for (int i=0; i < v_pos.size(); i++)
//     {
//         std::cout << "v:";
//         for (double d: v_pos[i])
//         {
//             std::cout << "   " << d;
//         }
//         std::cout << '\n';
//     }

//     for (int i=0; i < v_tex.size(); i++)
//     {
//         std::cout << "vt:";
//         for (double d: v_tex[i])
//         {
//             std::cout << "   " << d;
//         }
//         std::cout << '\n';
//     }

//     for (std::pair<int, int> p: f_pos_tex_set)
//     {
//         std::cout << p.first << " " << p.second;
//         std::cout << '\n';
//     }

//     for (std::vector<int> vec: polygons)
//     {
//         std::cout << "pol: ";
//         for (auto pol: vec)
//         {
//             std::cout << "   " << pol;
//         }
//         std::cout << '\n';
//     }
// }
