#include "ourcamera.h"
#include "h.h"

OurCamera::OurCamera() {
    position = QVector3D(0.0f, 0.0f, 3.0f);
    orientation = QQuaternion(1.0f, 0.0f, 0.0f, 0.0f);

    sense = 0.2;
    // speed = 1.2*delta_time;
    world_up = QVector3D(0.0f, 1.0f, 0.0f);
    update_cam_vectors();
}


void OurCamera::update_cam_vectors()
{
    front = (orientation*cam_front_start).normalized();
    right = (orientation*cam_right_start).normalized();
    up = (orientation*cam_up_start).normalized();
    // speed = 1.2*delta_time;
    update_view();
    update_projection();
}

QMatrix4x4 &OurCamera::get_view()
{
    return view;
}

void OurCamera::update_view()
{
    view.setToIdentity();
    view.lookAt(
        position,
        position+front,
        up);
}

QMatrix4x4 &OurCamera::get_projection()
{
    return projection;
}

void OurCamera::update_projection()
{
    projection.setToIdentity();
    projection.perspective(glm::radians(45.0f), HEIGHT/WIDTH, 0.05f, 50.0f);
}

void OurCamera::mouse_move_event(QMouseEvent *event)
{
    QPointF cur_pos = event->pos();
    QPointF d_pos = cur_pos-last_pos;
    last_pos = cur_pos;
    if (event->buttons())
    {
        object_rotation(d_pos.x(), d_pos.y());
    }
}

void OurCamera::mouse_press_event(QMouseEvent *event)
{
    last_pos = event->pos();
}

void OurCamera::object_rotation(float dx, float dy)
{
    dx = dx*sense;
    dy = dy*sense;
    QQuaternion qx = QQuaternion::fromAxisAndAngle(world_up, dx);
    QQuaternion qy = QQuaternion::fromAxisAndAngle(right, dy);
    orientation =  (qx*qy)*orientation;
    orientation.normalize();
    update_view();
}

void OurCamera::deb_camera()
{
    qDebug() << orientation;
}
