#ifndef FBO_H
#define FBO_H

#include "rend.h"
#include "h.h"


class OurCamera;
class FBO: public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(float q_angle READ get_angle WRITE set_angle NOTIFY angle_changed)
public:
    Renderer* createRenderer() const override;
    explicit FBO(QQuickItem* parent = nullptr);
    ~FBO();
    Q_INVOKABLE void set_angle(float a) {if (a == q_angle) return; q_angle=a; emit angle_changed(); update();}
    Q_INVOKABLE float get_angle() const {return q_angle;}
    // OurCamera get_camera() const {return *camera;}

    Q_INVOKABLE virtual void mousePressEvent(float x, float y, int press_type);
    Q_INVOKABLE virtual void mouseMoveEvent(float x, float y, int press_type);
    Q_INVOKABLE virtual void mouseReleaseEvent(float x, float y, int press_type);

    Q_INVOKABLE virtual void keyPressEvent(QKeyEvent *event) override;
    Q_INVOKABLE virtual void keyReleaseEvent(QKeyEvent *event) override;

// private?
    OurCamera *camera;
    float q_angle = 0;
    bool pressed = false;
    bool pressed_k = false;
signals:
    void angle_changed();
};

#endif // FBO_H
