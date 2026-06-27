#ifndef LOADMODEL_H
#define LOADMODEL_H

#include "h.h"

class OurObject;
class LoadModel
{
public:
    void get_info(const std::string path);
    // void show_all();
    OurObject * fill_info();
    // OurObject create_our_object();

    QVector<QVector3D> v_pos;
    QVector<QVector2D> v_tex;
    std::set<std::pair<int, int>> f_pos_tex_set;
    QVector<QVector<int>> polygons;
};

#endif // LOADMODEL_H
