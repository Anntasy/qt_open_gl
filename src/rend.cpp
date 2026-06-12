#include "rend.h"
#include "h.h"

Rend::Rend(): QQuickFramebufferObject::Renderer() { // FBO
    std::cout << "Rend\n";

    initializeOpenGLFunctions();

    all_data = new AllData();
    m_program = new QOpenGLShaderProgram();
    camera = new OurCamera();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex_shader.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragment_shader.frag");

    m_program->link();
    set_picture();
}

Rend::~Rend()
{
    delete all_data;
    delete m_program;
    delete camera;
}

QOpenGLFramebufferObject* Rend::createFramebufferObject(const QSize &size)
{
    initializeOpenGLFunctions();
    QOpenGLFramebufferObjectFormat format;
    int smooth = 0;

    format.setAttachment(QOpenGLFramebufferObject::Depth);
    format.setSamples(smooth);
    format.setInternalTextureFormat(GL_RGBA8);
    format.setTextureTarget(GL_TEXTURE_2D);

    q_size = size;
    return new QOpenGLFramebufferObject(size, format);
}

void Rend::synchronize(QQuickFramebufferObject* t)
{
    auto * it = dynamic_cast<FBO*>(t);
    *camera = *(it->camera);
    // qDebug() << "front  " << camera->front << "\n";
    // *camera = it->get_camera();
    // q_angle  = it->get_angle();
    // qDebug() << "syncc  " << "\n";
}

void Rend::set_picture() // FBO
{
    // all_data->add_triangle(0.25f, 0.25f, 1.0f, 0.25f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f);
    // all_data->add_triangle(0.1f, 0.1f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    // all_data->add_cube({-3.5f, -3.5f, 0.0f}, {-3.5f, 0.5f, 0.0f}, {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.1f});
    all_data->add_model("/home/vboxuser/Downloads/flowerr.obj");
    // all_data->add_rectangle(0.05f, 0.05f, 1.0f, 0.5f, 0.0f, 1.0f, 0.0f);

    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    // all_data->init(f);

    OurObject * o = all_data->object_l[0];
    // QVector<Vertex> vertices;
    // QVector<Element> indices;

    for (int i=0; i<o->vertices.size(); i++)
    {
        qDebug() << "V_pos: " << o->vertices[i].position << "\n";
    }

    for (int i=0; i<o->indices.size(); i++)
    {
        qDebug() << "I: " << o->indices[i].triangle[0] << " " << o->indices[i].triangle[1] << " " << o->indices[i].triangle[2] << "\n";
    }
}

// void Rend::render()
// {
//     camera->update_cam_vectors();
//     glViewport(0, 0, WIDTH, HEIGHT);

//     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     m_program->bind();

//     QMatrix4x4 transformation;

//     // initializeOpenGLFunctions();//!!!
//     QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();

//     float vertices[] = {
//     0.0f,  0.6f, 0.0f,
//     -0.6f, -0.6f, 0.0f,
//     0.6f, -0.6f, 0.0f
// };
//     float colors[] = {
//         0.0f, 1.0f, 0.0f,
//         0.0f, 1.0f, 1.0f,
//         1.0f, 0.0f, 1.0f
//     };

//     unsigned int texture_coords[] = {0, 0, 0, 1, 1, 1};

//     glActiveTexture(GL_TEXTURE0);
//     all_data->tex1->bind();
//     m_program->setUniformValue("texture_sample1", 0);
//     m_program->enableAttributeArray(0);
//     m_program->enableAttributeArray(1);
//     m_program->enableAttributeArray(2);

//     m_program->setAttributeArray(0, GL_FLOAT, vertices, 3);
//     m_program->setAttributeArray(1, GL_FLOAT, colors, 3);
//     m_program->setAttributeArray(2, GL_UNSIGNED_INT, texture_coords, 2);

//     transformation = camera->get_projection()*camera->get_view();
//     transformation.setToIdentity();
//     m_program->setUniformValue("transformation", transformation);
//     glDrawArrays(GL_TRIANGLES, 0, 3);

//     m_program->disableAttributeArray(0);
//     m_program->disableAttributeArray(1);
//     m_program->disableAttributeArray(2);
//     m_program->release();
//     all_data->tex1->release();

//     update();
// }


void Rend::render()
{
    // camera->update_cam_vectors();
    // // initializeOpenGLFunctions();//!!!
    // QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    // // glViewport(0, 0, q_size.width(), q_size.height());

    // glViewport(0, 0, q_size.width(), q_size.height());

    // glEnable(GL_DEPTH_TEST);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // m_program->bind();

    // QMatrix4x4 transformation;

    // // int start_i = 0;
    // glActiveTexture(GL_TEXTURE0);
    // all_data->tex1->bind();
    // m_program->setUniformValue("texture_sample1", 0);
    // // m_program->enableAttributeArray(0);
    // // m_program->enableAttributeArray(1);
    // // m_program->enableAttributeArray(2);

    // QMatrix4x4 model_obj;
    // OurObject *cur_obj;

    // for (int i=0; i<all_data->object_l.size(); i++)
    // {
    //     cur_obj = all_data->object_l[i];
    //     cur_obj->vao->bind();

    //     model_obj.translate((cur_obj->model)); // toQVector3D
    //     transformation = camera->get_projection()*camera->get_view()*model_obj;

    //     m_program->setUniformValue("transformation", transformation);

    //     // qDebug() << transformation;

    //     glDrawElements(GL_TRIANGLES, cur_obj->indices.size()*3, GL_UNSIGNED_INT, (void *)(0));
    //     // start_i += cur_obj->indices.size()*sizeof(Element);
    //     cur_obj->vao->release();
    // }
    // // GLenum err;
    // // while ((err = glGetError()) != GL_NO_ERROR) {
    // //     qDebug() << "OpenGL error:" << err;
    // // }
    // // m_program->disableAttributeArray(0);
    // // m_program->disableAttributeArray(1);
    // // m_program->disableAttributeArray(2);
    // m_program->release();
    // all_data->tex1->release();

    update();
}
