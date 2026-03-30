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
    Rend(); // FBO*
    virtual ~Rend();

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;


    // void rend_init() {initializeOpenGLFunctions();}
    void synchronize(QQuickFramebufferObject* t);
    void render() override;
    void set_picture();

    QSize q_size;
    float q_angle;
    QOpenGLShaderProgram* m_program; // FBO
    AllData *all_data; // FBO
    OurCamera *camera; //  FBo

    // FBO *link
};

#endif // REND_H

