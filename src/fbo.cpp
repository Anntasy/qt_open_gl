#include "fbo.h"

FBO::FBO() {}

QQuickFramebufferObject::Renderer* FBO::createRenderer() const
{
    return new Rend();
}
