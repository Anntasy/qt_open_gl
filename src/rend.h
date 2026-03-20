#ifndef REND_H
#define REND_H

#include "alldata.h"
#include "h.h"

class AllData;
class OurCamera;

// using AllData;
class Rend: public QQuickFramebufferObject::Renderer, protected QOpenGLExtraFunctions
{
public:
    Rend();
    virtual ~Rend() {}

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;


    // void rend_init() {initializeOpenGLFunctions();}
    void synchronize(QQuickFramebufferObject* t);
    void render() override;
    void set_picture();

    QSize q_size;
    float q_angle;
    QOpenGLShaderProgram* m_program;
    AllData *all_data;
    OurCamera *camera;
};

inline QVector3D toQVector3D(const glm::dvec3& v)
{
    return QVector3D(static_cast<float>(v.x),
                     static_cast<float>(v.y),
                     static_cast<float>(v.z));
}

#endif // REND_H

