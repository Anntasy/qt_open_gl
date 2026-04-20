#include "ourwidget.h"
#include "h.h"


OurWidget::OurWidget(QWidget* parent): QOpenGLWidget(parent)
{
    fbo = new FBO;
    // rend = fbo->createRenderer();
    rend = dynamic_cast<Rend *>(fbo->createRenderer());
}


OurWidget::~OurWidget()
{
    delete fbo;
    delete rend;
}

void OurWidget::initializeGL()
{
    rend->camera->update_cam_vectors();
    rend->camera->update_view();
    rend->camera->update_projection();
}


void OurWidget::paintGL()
{
    rend->render();
}

void OurWidget::mousePressEvent(QMouseEvent* e)
{
    rend->camera->mouse_press_event(e);
}


void OurWidget::mouseMoveEvent(QMouseEvent* e)
{
    rend->camera->mouse_move_event(e);
}
