#include "ourcamera.h"

OurCamera::OurCamera() {
    position = glm::dvec3(0.0f, 0.0f, 3.0f);
    orientation = glm::dquat(1.0f, 0.0f, 0.0f, 0.0f);

    sense = 1.e-5*2;
    // speed = 1.2*delta_time;
    world_up = glm::dvec3(0.0f, -1.0f, 0.0f);
    update_cam_vectors();
}


void OurCamera::update_cam_vectors()
{
    front = glm::normalize(orientation*cam_front_start);
    right = glm::normalize(orientation*cam_right_start);
    up = glm::normalize(orientation*cam_up_start);
    // speed = 1.2*delta_time;
}

QMatrix4x4 OurCamera::get_view()
{
    QMatrix4x4 matr;
    matr.lookAt(
        toQVector3D(position),
        toQVector3D(position+front),
        toQVector3D(up));
    return matr;
}
