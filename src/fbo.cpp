#include "fbo.h"

FBO::FBO(QQuickItem* parent): QQuickFramebufferObject(parent)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(QQuickItem::ItemHasContents, true);
    setAcceptHoverEvents(true);
    camera = new OurCamera();
}

FBO::~FBO()
{
    delete camera;
}

QQuickFramebufferObject::Renderer* FBO::createRenderer() const
{
    return new Rend(); //FBO  link
}


void FBO::mousePressEvent(QMouseEvent* e)
{
    camera->mouse_press_event(e);
}


void FBO::mouseMoveEvent(QMouseEvent* e)
{
    camera->mouse_move_event(e);
}
