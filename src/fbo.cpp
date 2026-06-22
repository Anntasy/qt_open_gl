#include "fbo.h"

FBO::FBO(QQuickItem* parent): QQuickFramebufferObject(parent)
{
    std::cout << "FBO\n";
    std::cout << parent << '\n';
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
    std::cout << "create rend\n";
    return new Rend(); //FBO  link
}


void FBO::mousePressEvent(float x, float y, int press_type)
{
    // std::cout << "press" << x << y << std::endl;
    pressed = true;
    camera->mouse_press_event(x, y, press_type);
    update();
}


void FBO::mouseMoveEvent(float x, float y, int press_type)
{
    // std::cout << "mvpe" << x << y << std::endl;
    if (!pressed)
        return;
    camera->mouse_move_event(x, y, press_type);
    update();
}

void FBO::mouseReleaseEvent(float x, float y, int press_type)
{
    // std::cout << "reel" << x << y << std::endl;
    pressed = false;
    update();
}

void FBO::keyReleaseEvent(QKeyEvent *event)
{
    pressed_k = false;
    update();
}

void FBO::keyPressEvent(QKeyEvent *event)
{
    pressed_k = true;
    if (camera->key_press_event(event))
    {
        update();
        event->accept();
    }
    QQuickFramebufferObject::keyPressEvent(event);
}
