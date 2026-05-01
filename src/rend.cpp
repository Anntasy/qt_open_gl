#include "rend.h"
#include "h.h"

Rend::Rend(): QQuickFramebufferObject::Renderer() { // FBO
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
    // format.setTextureTarget(GL_TEXTURE_2D);

    q_size = size;
    return new QOpenGLFramebufferObject(size, format);
}

void Rend::synchronize(QQuickFramebufferObject* t)
{
    auto * it = dynamic_cast<FBO*>(t);
    *camera = *(it->camera);
    // *camera = it->get_camera();
    // q_angle  = it->get_angle();
    qDebug() << "syncc  " << "\n";
}

void Rend::set_picture() // FBO
{
    // all_data->add_triangle(0.25f, 0.25f, 1.0f, 0.25f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f);
    // all_data->add_triangle(0.05f, 0.05f, 2.0f, 1.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f);
    all_data->add_cube({-3.5f, -3.5f, 0.0f}, {-3.5f, 0.5f, 0.0f}, {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.1f});
    // all_data->add_rectangle(0.05f, 0.05f, 1.0f, 0.5f, 0.0f, 1.0f, 0.0f);
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    all_data->init(f);
}

void Rend::render()
{
    camera->update_cam_vectors();
    initializeOpenGLFunctions();//!!!
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    glViewport(0, 0, q_size.width(), q_size.height());

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    m_program->bind();
    all_data->vao.bind();


    // QMatrix4x4 view = camera->get_view();
    // QMatrix4x4 projection;

    QMatrix4x4 transformation;

    int start_i = 0;
    glActiveTexture(GL_TEXTURE0);
    all_data->tex1->bind();
    m_program->setUniformValue("texture_sample1", 0);

    for (int i=0; i<all_data->object_l.size(); i++)
    {
        auto cur_obj = &all_data->object_l[i];
        QMatrix4x4 model_obj;
        model_obj.translate((cur_obj->model)); // toQVector3D
        transformation = camera->get_projection()*camera->get_view()*model_obj;

        m_program->setUniformValue("transformation", transformation);

        qDebug() << transformation;

        glDrawElements(GL_TRIANGLES, cur_obj->indices.size()*3, GL_UNSIGNED_INT, (void *)(start_i));
        start_i += cur_obj->indices.size()*sizeof(Element);
    }
    camera->deb_camera();
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void *)0);
    all_data->vao.release();
    m_program->release();
    all_data->tex1->release();

    update();
}
