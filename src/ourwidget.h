#ifndef OURWIDGET_H
#define OURWIDGET_H

#include "h.h"

// class OurWidget
// {
// public:
//     OurWidget();
// };

class FBO;
class Rend;
class OurWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OurWidget(QWidget* parent = nullptr);
    ~OurWidget() override;

protected:
    void initializeGL() override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    // void keyPressEvent(QKeyEvent* e) override;

// private:
//     void initShaders();
//     void initGeometry();
//     void releaseGlResources();

private:
    // QOpenGLShaderProgram program_;
    // GLuint vao_ = 0;
    // GLuint vbo_ = 0;
    // QTimer timer_;
    FBO *fbo;
    Rend *rend;
};
#endif // OURWIDGET_H
