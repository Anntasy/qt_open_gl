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

    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;

// private?
    OurCamera *camera;
    float q_angle = 0;
signals:
    void angle_changed();
};

#endif // FBO_H
