#ifndef REND_H
#define REND_H

#include <QQuickFramebufferObject>

class Rend: QQuickFramebufferObject::Renderer
{
public:
    void render() override;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;
    Rend();
};

#endif // REND_H
