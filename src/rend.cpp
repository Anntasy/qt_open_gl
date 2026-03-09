#include "rend.h"

Rend::Rend() {}


QOpenGLFramebufferObject* Rend::createFramebufferObject(const QSize &size)
{
    initializeOpenGLFunctions();
    QOpenGLFramebufferObjectFormat format;
    int smooth = 0;

    format.setAttachment(QOpenGLFramebufferObject::Depth);
    format.setSamples(smooth);
    format.setInternalTextureFormat(GL_RGBA8);
    // format.setTextureTarget(GL_TEXTURE_2D);

    q_size = size;
    return new QOpenGLFramebufferObject(size, format);
}

void Rend::synchronize(QQuickFramebufferObject* t)
{
    auto * it = static_cast<FBO*>(t);
    q_angle  = it->get_angle();
}

void Rend::render()
{
    initializeOpenGLFunctions();
    glViewport(0, 0, q_size.width(), q_size.height());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    update();
}
