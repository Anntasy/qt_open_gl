#ifndef OURCAMERA_H
#define OURCAMERA_H

#include "h.h"


class OurCamera
{
public:
    OurCamera();
    ~OurCamera() {}

    QMatrix4x4 get_view();
    // void process_keyboard();
    // void process_mouse(double d_x, double d_y);
    void update_cam_vectors();


    glm::dvec3 cam_front_start = glm::dvec3(0.0f, 0.0f, -1.0f);
    glm::dvec3 cam_up_start = glm::dvec3(0.0f, -1.0f, 0.0f);
    glm::dvec3 cam_right_start = glm::dvec3(-1.0f, 0.0f, 0.0f);

    glm::dvec3 front;
    glm::dvec3 up;
    glm::dvec3 right;
    glm::dvec3 position;
    glm::float64 Yaw;
    glm::float64 Pitch;
    double sense;
    glm::float64 speed;
    glm::dvec3 world_up;
    glm::dquat orientation;
};


extern OurCamera our_camera;

# endif
