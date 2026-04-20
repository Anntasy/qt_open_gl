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
    void synchronize(QQuickFramebufferObject* t) override;
    void render() override;
    void set_picture();
    void mouse_move_event(QMouseEvent* q_event);
    void mouse_press_event(QMouseEvent* q_event);

    QSize q_size;
    float q_angle;
    QOpenGLShaderProgram* m_program; // FBO
    AllData *all_data; // FBO
    OurCamera *camera; //  FBo

    // FBO *link
};

#endif // REND_H

