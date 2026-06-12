#include "ourcamera.h"
#include "h.h"

OurCamera::OurCamera() {
    std::cout << "Camera\n";
    position = QVector3D(0.0f, 0.0f, 3.0f);
    orientation = QQuaternion(1.0f, 0.0f, 0.0f, 0.0f);

    sense = 0.2;
    // speed = 1.2*delta_time;
    speed = 0.8;
    world_up = QVector3D(0.0f, 1.0f, 0.0f);
    update_cam_vectors();
}


OurCamera::OurCamera(unsigned int width_, unsigned int height_): OurCamera::OurCamera() {
    std::cout << "Camera param\n";
    width = width_;
    height = height_;
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
    projection.perspective(60.0f, height/width, 0.05f, 50.0f);
}

void OurCamera::mouse_move_event(float x, float y, int press_type)
{
    QPointF cur_pos(x, y);
    QPointF d_pos = cur_pos-last_pos;
    last_pos = cur_pos;
    // std::cout << cur_pos.x()  << " " << cur_pos.y() << "\n";
    // if (press_type)
    // {
    //     object_rotation(d_pos.x(), d_pos.y());
    // }
    object_rotation(d_pos.x(), d_pos.y());
    // update_cam_vectors();
}

void OurCamera::mouse_press_event(float x, float y, int press_type)
{
    last_pos.setX(x);
    last_pos.setY(y);
    // update_cam_vectors();
}

int OurCamera::key_press_event(QKeyEvent *event)
{
    update_cam_vectors();
    if (event->key() == Qt::Key_W)
    {
        position += speed*front;
        // qDebug() << "W" << position << "\n";
        // position += QVector3D(0.0f, 0.0f, 0.005f);
        return 1;
    }
    if (event->key() == Qt::Key_S)
    {
        position -= speed*front;
        // qDebug() << "S" << position << "\n";
        // position -= QVector3D(0.0f, 0.0f, 0.005f);
        return 1;
    }
    if (event->key() == Qt::Key_A)
    {
        position -= speed*right;
        // qDebug() << "A" << position << "\n";
        return 1;
    }
    if (event->key() == Qt::Key_D)
    {
        position += speed*right;
        // qDebug() << "D" << position << "\n";
        return 1;
    }
    return 0;
}

void OurCamera::object_rotation(float dx, float dy)
{
    dx = dx*sense;
    dy = dy*sense*(-1);
    QQuaternion qx = QQuaternion::fromAxisAndAngle(world_up, dx);
    QQuaternion qy = QQuaternion::fromAxisAndAngle(right, dy);
    orientation = (qx*qy)*orientation;
    orientation.normalize();
    // deb_camera();
    // update_view();
}

void OurCamera::deb_camera()
{
    qDebug() << "orientation " << orientation << "\n";
    qDebug() << "projection"  << projection << "\n";
    qDebug() << "view"  << view << "\n";
    qDebug() << "front"  << front << "\n";
}
