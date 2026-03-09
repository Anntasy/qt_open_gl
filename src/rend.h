#ifndef REND_H
#define REND_H

#include "h.h"

class Rend: public QQuickFramebufferObject::Renderer, protected QOpenGLExtraFunctions
{
public:
    void render() override;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;
    Rend();

    void rend_init() {initializeOpenGLFunctions();}

    QSize q_size;
    float q_angle;
    void synchronize(QQuickFramebufferObject* t);
};

#endif // REND_H

