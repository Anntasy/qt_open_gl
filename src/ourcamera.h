#ifndef OURCAMERA_H
#define OURCAMERA_H

#include "h.h"


class OurCamera
{
public:
    OurCamera();
    OurCamera(unsigned int width_, unsigned int height_);
    ~OurCamera() {}

    QMatrix4x4 &get_view();
    QMatrix4x4 &get_projection();
    // void process_keyboard();
    // void process_mouse(double d_x, double d_y);
    void update_cam_vectors();
    void update_view();
    void update_projection();
    void object_rotation(float dx, float dy);
    void mouse_move_event(float x, float y, int press_type);
    void mouse_press_event(float x, float y, int press_type);

    int key_press_event(QKeyEvent *event);

    void deb_camera();

    QVector3D cam_front_start = QVector3D(0.0f, 0.0f, -1.0f);
    QVector3D cam_up_start = QVector3D(0.0f, 1.0f, 0.0f);
    QVector3D cam_right_start = QVector3D(1.0f, 0.0f, 0.0f);

    QVector3D front;
    QVector3D up;
    QVector3D right;
    QVector3D position;
    unsigned int width;
    unsigned int height;
    double sense;
    glm::float64 speed;
    QVector3D world_up;
    QPointF last_pos;
    QQuaternion orientation;

    QMatrix4x4 view;
    QMatrix4x4 projection;
};


inline QVector3D toQVector3D(const glm::vec3& v)
{
    return QVector3D(static_cast<float>(v.x),
                     static_cast<float>(v.y),
                     static_cast<float>(v.z));
}

#endif // OURCAMERA_H
