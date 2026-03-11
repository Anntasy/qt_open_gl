#ifndef REND_H
#define REND_H

#include "alldata.h"
#include "h.h"

class AllData;

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
};

#endif // REND_H

