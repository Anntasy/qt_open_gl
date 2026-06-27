#include "loadmodel.h"



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
        Element e1 = {{poly[0]-1, poly[1]-1, poly[2]-1}};
        Element e2 = {{poly[0]-1, poly[2]-1, poly[3]-1}};
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
