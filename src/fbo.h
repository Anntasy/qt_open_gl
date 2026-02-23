#ifndef FBO_H
#define FBO_H

#include <QQuickFramebufferObject>

class FBO: QQuickFramebufferObject
{
public:
    Renderer* createRenderer() const override;
    FBO();
};

#endif // FBO_H
